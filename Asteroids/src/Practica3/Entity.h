#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <array>
#include <bitset>
#include <functional>

#include "Component.h"
#include "DefaultFactory.h"
#include "SDLGame.h"
#include "ECS.h"

// We don't include the EntityManager class to avoid circular dependeincies
class EntityManager;

class Entity {

	// defining a type just for brevity
	using ComponentPtr = std::unique_ptr<Component, std::function<void(Component*)>>;

public:
	Entity() :
		game_(SDLGame::instance()), //
		manager_(nullptr), //
		active_(true) {
	}

	virtual ~Entity() {
	}

	inline EntityManager* getEntityMngr() const {
		return manager_;
	}

	inline void setEntityMngr(EntityManager* mngr) {
		manager_ = mngr;
	}

	inline bool isActive() const {
		return active_;
	}

	inline void setActive(bool active) {
		active_ = active;
	}

	template<typename T>
	inline T* getComponent(ECS::CmpIdType id) {
		return static_cast<T*>(componentArray_[id].get());
	}

	template<typename T>
	inline bool hasComponent(ECS::CmpIdType id) {
		return componentArray_[id] != nullptr;
	}

	template<typename T, typename FT = DefaultFactory<T>, typename ... Targs>
	inline T* addComponent(Targs&&...args) {

		// create the actual component ...
		T* c = FT::construct(std::forward<Targs>(args)...);
		ComponentPtr uPtr(c, [](Component* p) {
			FT::destroy(static_cast<T*>(p));
			});

		// store it in the components array
		componentArray_[c->id_] = std::move(uPtr);

		return c;
	}

	template<typename T>
	inline void removeComponent(ECS::CmpIdType id) {
		componentArray_[id] = nullptr;
	}

	// defined in CPP since it access the manager
	void addToGroup(ECS::GrpIdType id);

	inline void removeFromGroup(ECS::GrpIdType grpId) {
		groups_[grpId] = false;
	}

	inline void resetGroups() {
		groups_.reset();
	}

	inline bool hasGroup(ECS::GrpIdType grpId) {
		return groups_[grpId];
	}

private:
	SDLGame* game_;
	EntityManager* manager_;

	std::array<ComponentPtr, ECS::maxComponents> componentArray_ = { };
	std::bitset<ECS::maxGroups> groups_;

	bool active_;
};

#endif // !__ENTITY_H__