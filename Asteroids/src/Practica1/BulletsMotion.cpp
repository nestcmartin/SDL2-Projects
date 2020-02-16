#include "BulletsMotion.h"
#include "Entity.h"
#include "Bullet.h"

BulletsMotion::BulletsMotion() :
	Component(ECS::BulletsMotion),
	bulletsPool_(nullptr)
{
}

BulletsMotion::~BulletsMotion()
{
}

void BulletsMotion::init()
{
	bulletsPool_ = GETCMP1_(BulletsPool);
}

void BulletsMotion::update()
{
	std::vector<Bullet*> bullets = bulletsPool_->getPool();

	for (Bullet* b : bullets)
	{
		if (b->getActive())
		{
			Vector2D newPos = b->getPos() + b->getVel();

			if (newPos.getX() < 0 || newPos.getX() >= game_->getWindowWidth() ||
				newPos.getY() < 0 || newPos.getY() >= game_->getWindowHeight())
				b->setActive(false);
			b->setPos(newPos);
		}
	}
}