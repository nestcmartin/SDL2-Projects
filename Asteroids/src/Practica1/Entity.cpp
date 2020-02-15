#include "Entity.h"

Entity::Entity(SDLGame* game, EntityManager* mngr) :
	game_(game),
	entityManager_(mngr)
{
}

Entity::~Entity() 
{
}

void Entity::update()
{
	for (auto& c : components_)
	{
		c->update();
	}
}

void Entity::draw()
{
	for (auto& c : components_) 
	{
		c->draw();
	}
}