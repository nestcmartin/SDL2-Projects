#include "Gun.h"
#include "Entity.h"
#include "InputHandler.h"

Gun::Gun() :
	Component(ECS::Gun),
	transform_(nullptr),
	bulletsPool_(nullptr),
	fireKey_(SDL_Keycode())
{
}

Gun::Gun(SDL_Keycode fire, BulletsPool* pool) :
	Component(ECS::Gun),
	transform_(nullptr),
	bulletsPool_(pool),
	fireKey_(fire)
{
}

Gun::~Gun()
{
}

void Gun::init()
{
	transform_ = GETCMP1_(Transform);
}

void Gun::update()
{
	if (InputHandler::instance()->isKeyDown(fireKey_))
	{
		if (bulletsPool_ && game_->getCurrentTime() - lastShootTime_ >= COOLDOWN_TIME)
		{
			Vector2D p = transform_->getPos();
			double w = transform_->getW();
			double h = transform_->getH();
			double r = transform_->getRot();

			Vector2D bulletPos = p + Vector2D(w / 2, h / 2) + Vector2D(0, -(h / 2 + 5.0)).rotate(r);
			Vector2D bulletVel = Vector2D(0, -1).rotate(r) * BULLET_SPEED;

			bulletsPool_->shoot(bulletPos, bulletVel, 5, 5);
			lastShootTime_ = game_->getCurrentTime();
			game_->getAudioManager()->playChannel(Resources::GunShot, 0);
		}
	}
}
