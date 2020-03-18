#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include "System.h"

#include "EntityManager.h"
#include "Collisions.h"
#include "StarsSystem.h"

#include "Transform.h"

class CollisionSystem : public System 
{
public:

	void update() 
	{
		auto ptr = entityManager_->getHandler<_hdlr_PacMan>()->getComponent<Transform>();
		for (auto& e : entityManager_->getGroupEntities<_grp_Star>()) 
		{
			auto etr = e->getComponent<Transform>();
			if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) 
			{
				entityManager_->getSystem<StarsSystem>()->onCollision(e);
			}
		}
	}
};

#endif // !__COLLISION_SYSTEM_H__