#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "StarsSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:

	void update() {
		auto ptr = mngr_->getHandler<_hdlr_PacMan>()->getComponent<Transform>();
		for( auto& e : mngr_->getGroupEntities<_grp_Star>()) {
			auto etr = e->getComponent<Transform>();
			if ( Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
				mngr_->getSystem<StarsSystem>()->onCollision(e);
			}
		}
	}
};

