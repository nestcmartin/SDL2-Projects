#include "Entity.h"
#include "Manager.h"

void Entity::addToGroup(std::size_t id) {
	groups_[id] = true;
	mngr_->addToGroup(id,this);
}
