#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <array>
#include <bitset>
#include <functional>

#include "DefaultFactory.h"

#include "Component.h"

#include "ECS.h"
#include "SDLGame.h"


class EntityManager;

class Entity
{
	using ComponentPtr = std::unique_ptr<Component, std::function<void(Component*)>>;

private:
	SDLGame* game_;
	EntityManager* entityManager_;

	std::array<ComponentPtr, ECS::maxComponents> components_ = { };
	std::bitset<ECS::maxGroups> groups_;

	bool active_;

public:
	Entity() :
		game_(SDLGame::instance()),
		entityManager_(nullptr),
		active_(true) 
	{
	}

	virtual ~Entity() 
	{
	}

	inline EntityManager* getEntityManager() const { return entityManager_; }
	inline void setEntityManager(EntityManager* mngr) { entityManager_ = mngr; }
	inline bool isActive() const { return active_; }
	inline void setActive(bool active) { active_ = active; }

	template<typename T> inline T* getComponent(ECS::ComponentId id) { return static_cast<T*>(components_[id].get()); }
	template<typename T> inline bool hasComponent(ECS::ComponentId id) { return components_[id] != nullptr; }
	template<typename T> inline void removeComponent(ECS::ComponentId id) { components_[id] = nullptr; }
	template<typename T, typename FT = DefaultFactory<T>, typename ... Targs>
	inline T* addComponent(Targs&&...args) 
	{
		T* c = FT::construct(std::forward<Targs>(args)...);
		ComponentPtr uPtr(c, [](Component* p) {
			FT::destroy(static_cast<T*>(p));
			});

		components_[c->id_] = std::move(uPtr);

		return c;
	}

	inline void resetGroups() { groups_.reset(); }
	inline bool hasGroup(ECS::GroupId grpId) { return groups_[grpId]; }
	inline void removeFromGroup(ECS::GroupId grpId) { groups_[grpId] = false; }
	void addToGroup(ECS::GroupId id);
};

#endif // !__ENTITY_H__