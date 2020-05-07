#ifndef __FIGHTER_GUN_SYSTEM_H__
#define __FIGHTER_GUN_SYSTEM_H__

#include <cstdint>

#include "Entity.h"
#include "EntityManager.h"

#include "Transform.h"

#include "System.h"
#include "BulletsSystem.h"

#include "SDL_Macros.h"

#include "SDLGame.h"

class FighterGunSystem : public System
{
private:
	Uint32 lastShootTime_ = 0;

public:
	void update() override
	{
		if (!entityManager_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->running_) return;

		if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
		{
			BulletsSystem* bs = entityManager_->getSystem<BulletsSystem>();
			
			if (bs && game_->getTime() - lastShootTime_ >= 250)
			{
				game_->getAudioManager()->playChannel(Resources::GunShot, 0);

				Transform* tr = entityManager_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();

				Vector2D bulletPos = tr->position_ + Vector2D(tr->width_ / 2, tr->height_ / 2) + Vector2D(0, -(tr->height_ / 2 + 5.0)).rotate(tr->rotation_);
				Vector2D bulletVel = Vector2D(0, -1).rotate(tr->rotation_) * 2.0;

				bs->shoot(bulletPos, bulletVel, 5, 5);
				lastShootTime_ = game_->getTime();
			}
		}
	}
};

#endif // !__FIGHTER_GUN_SYSTEM_H__