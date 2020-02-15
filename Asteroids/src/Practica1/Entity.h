#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <array>

#include "SDLGame.h"
#include "Component.h"
#include "EntityManager.h"

class Entity 
{
private:
	SDLGame* game_;
	EntityManager* entityManager_;

	std::vector<std::unique_ptr<Component>> components_;
	std::array<Component*, ECS::maxComponents> componentsArray_ = {};

public:
	Entity(SDLGame* game, EntityManager* mngr);
	virtual ~Entity();

	inline EntityManager* getEntityManager() { return entityManager_; }
	inline bool hasComponent(ECS::CmpIdType id) { return componentsArray_[id] != nullptr; }

	template<typename T, typename ...TArgs>
	T* addComponent(TArgs ...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr(c);
		components_.push_back(std::move(uPtr));
		componentsArray_[c->getId()] = c;
		c->setEntity(this);
		c->setGame(game_);
		c->init();
		return c;
	}

	template<typename T>
	T* getComponent(ECS::CmpIdType id)
	{
		return static_cast<T*>(componentsArray_[id]);
	}

	void update();
	void draw();
};

#endif // !__ENTITY_H__