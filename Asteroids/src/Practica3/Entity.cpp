#include "Entity.h"
#include "EntityManager.h"

void Entity::addToGroup(ECS::GrpIdType id) {
	groups_[id] = true;
	manager_->addToGroup(id,this);
}
