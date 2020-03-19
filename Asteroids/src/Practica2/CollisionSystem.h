#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include "EntityManager.h"

#include "Transform.h"

#include "System.h"
#include "FighterSystem.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"

#include "Collisions.h"

class CollisionSystem : public System 
{
public:
	void update() override
	{
		Transform* trFighter = entityManager_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();
		
		for (auto& a : entityManager_->getGroupEntities<_grp_Asteroid>()) 
		{
			Transform* trAsteroid = a->getComponent<Transform>();

			if (Collisions::collides(trFighter->position_, trFighter->width_, trFighter->height_,
				trAsteroid->position_, trAsteroid->width_, trAsteroid->height_))
			{
				entityManager_->getSystem<FighterSystem>()->onCollisionWithAsteroid(a);
				entityManager_->getSystem<GameCtrlSystem>()->onFighterDeath();
				break;
			}

			for (auto& b : entityManager_->getGroupEntities<_grp_Bullet>())
			{
				Transform* trBullet = b->getComponent<Transform>();

				if (!b->isActive()) continue;
				if (!a->isActive()) break;

				if (Collisions::collides(trAsteroid->position_, trAsteroid->width_, trAsteroid->height_,
					trBullet->position_, trBullet->width_, trBullet->height_))
				{
					entityManager_->getSystem<BulletsSystem>()->onCollisionWithAsteroid(b, a);
					entityManager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(a, b);

					if (!entityManager_->getSystem<AsteroidsSystem>()->asteroidsLeft())
					{
						entityManager_->getSystem<GameCtrlSystem>()->onAsteroidsExtinction();
						entityManager_->getSystem<FighterSystem>()->onCollisionWithAsteroid(nullptr);
					}
				}
			}
		}
	}
};

#endif // !__COLLISION_SYSTEM_H__