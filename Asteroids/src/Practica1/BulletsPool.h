#ifndef __BULLETS_POOL_H__
#define __BULLETS_POOL_H__

#include "Bullet.h"
#include "Asteroid.h"
#include "Component.h"
#include "ObjectPool.h"

class BulletsPool : public Component
{
private:
	ObjectPool<Bullet, 10> bulletsPool_ = ObjectPool<Bullet, 10>(&Bullet::getActive);

public:
	BulletsPool();
	virtual ~BulletsPool();

	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();
	void onCollision(Bullet* b, Asteroid* a);
	const std::vector<Bullet*>& getPool();
};

#endif // !__BULLETS_POOL_H__