#ifndef __BULLETS_SYSTEM_H__
#define __BULLETS_SYSTEM_H__

#include "Entity.h"
#include "EntityManager.h"
#include "BulletsPool.h"

#include "Transform.h"

#include "System.h"

#include "SDLGame.h"
#include "SDL_Macros.h"

class BulletsSystem : public System
{
public:
	void shoot(Vector2D pos, Vector2D vel, double width, double height)
	{
		Entity* e = entityManager_->addEntity<BulletsPool>(pos, vel, width, height);
		if (!e) return;
		e->addToGroup<_grp_Bullet>();
		e->setActive(true);
	}

	void onCollisionWithAsteroid(Entity* b, Entity* a)
	{
		b->setActive(false);
	}

	void update() override
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Bullet>())
		{
			if (!e->isActive()) return;

			Transform* tr = e->getComponent<Transform>();
			Vector2D newPos = tr->position_ + tr->velocity_;
			if (newPos.getX() < 0 || newPos.getX() >= game_->getWindowWidth() ||
				newPos.getY() < 0 || newPos.getY() >= game_->getWindowHeight())
				e->setActive(false);
			tr->position_ = newPos;
		}
	}

};

#endif // !__BULLETS_SYSTEM_H__
