#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <list>

#include "Entity.h"
#include "DefaultFactory.h"
#include "MemoryPool.h"

#include "System.h"

#include "Messages.h"

#include "SDLGame.h"
#include "ECS.h"

class EntityManager
{
	using EntityPtr = std::unique_ptr<Entity, std::function<void(Entity*)>>;
	using MessagePtr = std::unique_ptr<msg::Message, std::function<void(msg::Message*)>>;
	using EventType = std::function<void()>;

private:
	SDLGame* game_;

	std::vector<EntityPtr> entities_;
	std::array<Entity*, ECS::maxHandlers> handlers_;
	std::array<std::vector<Entity*>, ECS::maxGroups> groups_;
	std::array<std::unique_ptr<System>, ECS::maxSystems> systems_;

	std::list<MessagePtr>* messages_;
	std::list<std::function<void()>> events_;

public:
	EntityManager(SDLGame* game) :
		game_(game) 
	{
		messages_ = new std::list<MessagePtr>();
	}

	virtual ~EntityManager() 
	{
		delete messages_;
	}

	void refresh();

	const std::vector<EntityPtr>& getEntities() { return entities_; }
	const std::vector<Entity*>& getGroup(ECS::GroupId grpId) { return groups_[grpId]; }

	// Entities
	template<typename FT = DefaultFactory<Entity>, typename ...Targs>
	inline Entity* addEntity(Targs&&...args) 
	{
		Entity* e = FT::construct(std::forward<Targs>(args)...);
		if (e != nullptr) {
			e->setEntityManager(this);
			e->resetGroups();
			events_.push_back([this, e]() {
				entities_.emplace_back(e, [](Entity* p) {
					FT::destroy(p);
					});
				});
		}
		return e;
	}

	// Handlers
	inline Entity* getHandler(ECS::HandlerId id) { return handlers_[id]; }
	inline void setHandler(ECS::HandlerId id, Entity* e) { handlers_[id] = e; }

	// Groups
	inline void addToGroup(ECS::GroupId grpId, Entity* e)
	{
		events_.push_back([this, grpId, e]() {
			groups_[grpId].push_back(e);
			});
	}

	// Systems
	template<typename T, typename ...Targs>
	T* addSystem(Targs&&... args) 
	{
		T* s = new T(std::forward<Targs>(args)...);
		systems_[s->getId()] = std::unique_ptr<T>(s);
		s->setGame(game_);
		s->setManager(this);
		s->init();
		return s;
	}

	template<typename T>
	T* getSystem(ECS::SystemId id) 
	{
		return static_cast<T*>(systems_[id].get());
	}

	// Messaging
	template<typename T, typename FT = DefaultFactory<T>, typename ...Ts>
	void send(Ts&&...args) 
	{
		msg::Message* msg = FT::construct(std::forward<Ts>(args)...);
		MessagePtr uPtr(msg, [](msg::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});
		messages_->push_back(std::move(uPtr));
	}

	void flushMessages() 
	{
		while (!messages_->empty()) 
		{
			MessagePtr msg = std::move(messages_->front());
			for (auto& s : systems_) 
			{
				if (s != nullptr) 
					s->receive(*msg);
			}
			messages_->pop_front();
		}
	}
};

#endif // !__ENTITY_MANAGER_H__