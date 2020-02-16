#include "BulletsPool.h"

BulletsPool::BulletsPool() :
	Component(ECS::BulletsPool)
{	
}

BulletsPool::~BulletsPool()
{
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h)
{
	Bullet* b = bulletsPool_.getObj();

	if (b)
	{
		b->setPos(pos);
		b->setVel(vel);
		b->setRot(Vector2D(0, -1).angle(vel));
		b->setWH(w, h);
		b->setActive(true);
	}
}

void BulletsPool::disableAll()
{
	std::vector<Bullet*> bullets = getPool();
	for (Bullet* b : bullets) b->setActive(false);
}

void BulletsPool::onCollision(Bullet* b, Asteroid* a)
{
	b->setActive(false);
}

const std::vector<Bullet*>& BulletsPool::getPool()
{
	return bulletsPool_.getPool();
}
