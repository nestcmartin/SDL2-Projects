#include "Entity.h"
#include "EntityManager.h"

void Entity::addToGroup(ECS::GrpIdType id)
{
	groups_[id] = true;
	entityManager_->addToGroup(id, this);
}