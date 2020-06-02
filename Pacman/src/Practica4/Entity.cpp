#include "Entity.h"
#include "EntityManager.h"

void Entity::addToGroup(ECS::GroupId id) 
{
	groups_[id] = true;
	entityManager_->addToGroup(id,this);
}