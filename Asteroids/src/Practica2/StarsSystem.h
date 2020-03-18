#ifndef __STAR_SYSTEM_H__
#define __STAR_SYSTEM_H__

#include <cmath>

#include "System.h"

#include "Entity.h"
#include "EntityManager.h"
#include "StarsPool.h"

#include "Score.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "Transform.h"

#include "SDLGame.h"
#include "SDL_Macros.h"

class StarsSystem : public System 
{
public:
	void onCollision(Entity* s) 
	{
		s->setActive(false);
		auto sc = entityManager_->getHandler<_hdlr_GameState>()->getComponent<Score>();
		sc->points_++;
	}

	void addStars(std::size_t n) 
	{
		for (auto i(0u); i < n; i++) 
		{
			int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
			int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
			int w = game_->getRandGen()->nextInt(25, 50);
			int h = w;
			int r = game_->getRandGen()->nextInt(1, 2);
			Uint32 lt = game_->getRandGen()->nextInt(5, 10);

			Entity* e = entityManager_->addEntity<StarsPool>(x, y, w, h, r, lt);
			if (e != nullptr) e->addToGroup<_grp_Star>();
		}
	}

	void update() override 
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Star>()) 
		{
			if (!e->isActive()) return;

			Transform* tr = e->getComponent<Transform>();
			LifeTime* st = e->getComponent<LifeTime>();
			auto* rot = e->getComponent<Rotation>();
			tr->position_ = tr->position_ + tr->velocity_;
			tr->rotation_ += rot->rotation_;

			if (game_->getTime() - st->creationTime_ > st->lifeTime_) 
			{
				e->setActive(false);

				for (int i = 0; i < 2; i++) 
				{
					int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
					int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
					int w = game_->getRandGen()->nextInt(25, 50);
					int h = w;
					int r = game_->getRandGen()->nextInt(1, 2);
					Uint32 lt = game_->getRandGen()->nextInt(5, 10);

					Entity* e = entityManager_->addEntity<StarsPool>(x, y, w, h, r, lt);
					if (e != nullptr) e->addToGroup<_grp_Star>();
				}

			}

		}

	}
};

#endif // !__STAR_SYSTEM_H__