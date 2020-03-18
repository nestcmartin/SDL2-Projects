#include "Entity.h"
#include "EntityManager.h"

void Entity::addToGroup(std::size_t id) 
{
	groups_[id] = true;
	entityManager_->addToGroup(id, this);
}