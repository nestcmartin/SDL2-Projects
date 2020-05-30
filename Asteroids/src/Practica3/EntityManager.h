#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <list>
#include "SDLGame.h"
#include "DefaultFactory.h"
#include "ObjectFactory.h"
#include "ECS.h"
#include "Entity.h"
#include "messages.h"
#include "MemoryPool.h"
#include "System.h"

class EntityManager {
	using EntityPtr = std::unique_ptr<Entity, std::function<void(Entity*)>>;
	using MessagePtr = std::unique_ptr<messages::Message, std::function<void(messages::Message*)>>;
	using EventType = std::function<void()>;

public:
	EntityManager(SDLGame* game, const char* name) :
		game_(game),
		name_(name)
	{

		messages_ = new std::list<MessagePtr>();

		// needed only when using method flushMessages
		// that uses the std::swap
		// supportMsgs_ = new std::list<uptr_msg>();
	}

	virtual ~EntityManager() {
		delete messages_;
		// delete supportMsgs_;
	}

	// entities
	template<typename FT = DefaultFactory<Entity>, typename ...Targs>
	inline Entity* addEntity(Targs&&...args) {
		Entity* e = FT::construct(std::forward<Targs>(args)...);
		if (e != nullptr) {
			e->setEntityMngr(this);
			e->resetGroups();
			events_.push_back([this, e]() {
				entities_.emplace_back(e, [](Entity* p) {
					FT::destroy(p);
					});
				});
		}
		return e;
	}

	// groups
	inline void addToGroup(ECS::GrpIdType grpId, Entity* e) {
		events_.push_back([this, grpId, e]() {
			entityGroups_[grpId].push_back(e);
			});
	}

	// handlers
	inline void setHandler(ECS::HdlrIdType id, Entity* e) {
		handlers_[id] = e;
	}

	inline Entity* getHandler(ECS::HdlrIdType id) {
		return handlers_[id];
	}

	// systems
	template<typename T, typename ...Targs>
	T* addSystem(Targs&&... args) {
		T* s = new T(std::forward<Targs>(args)...);
		systems_[s->getId()] = unique_ptr<T>(s);
		s->setGame(game_);
		s->setMngr(this);
		s->init();
		return s;
	}

	template<typename T>
	T* getSystem(ECS::SysIdType id) {
		return static_cast<T*>(systems_[id].get());
	}

	// access to lists of entities
	const vector<Entity*>& getGroupEntities(ECS::GrpIdType grpId) {
		return entityGroups_[grpId];
	}

	const std::vector<EntityPtr>& getEntities() {
		return entities_;
	}

	// refresh lists of entities (remove not active and modify groups)
	void refresh();

	// messaging

	template<typename T, typename FT = ObjectFactory<T>, typename ...Ts>
	void send(Ts&&...args) {
		messages::Message* msg = FT::construct(std::forward<Ts>(args)...);
		msg->senderClientId = game_->getNetworking()->getClientId();
		MessagePtr uPtr(msg, [](messages::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});
		messages_->push_back(std::move(uPtr));
	}

	template<typename T, typename FT = ObjectFactory<T>, typename ...Ts>
	void forwardMsg(uint32_t clientId, Ts&&...args) {
		messages::Message* msg = FT::construct(std::forward<Ts>(args)...);
		msg->senderClientId = clientId;
		MessagePtr uPtr(msg, [](messages::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});
		messages_->push_back(std::move(uPtr));
	}

	void flushMessages() {

		while (!messages_->empty()) {
			MessagePtr msg = std::move(messages_->front());
			for (auto& s : systems_) {
				if (s != nullptr)
					s->receive(*msg);
			}
			messages_->pop_front();
		}
	}

	inline uint32_t getClientId() {
		return game_->getNetworking()->getClientId();
	}

	inline const char* getName() {
		return name_;
	}

private:
	SDLGame* game_;
	const char* name_;

	std::vector<EntityPtr> entities_;
	std::array<std::vector<Entity*>, ECS::maxGroups> entityGroups_;
	std::array<Entity*, ECS::maxHandlers> handlers_;
	std::array<unique_ptr<System>, ECS::maxSystems> systems_;

	std::list<std::function<void()>> events_;
	std::list<MessagePtr>* messages_;
	// std::list<uptr_msg> *supportMsgs_;

};

#endif // !__ENTITY_MANAGER_H__