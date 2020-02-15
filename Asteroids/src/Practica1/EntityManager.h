#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "SDLGame.h"

class Entity;

class EntityManager
{
private:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities_;

public:
	EntityManager(SDLGame* game);
	virtual ~EntityManager();

	void update();
	void draw();

	Entity* addEntity();
};

#endif // !__ENTITY_MANAGER_H__