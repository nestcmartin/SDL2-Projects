#ifndef __ASTEROIDS_POOL_H__
#define __ASTEROIDS_POOL_H__

#include "Bullet.h"
#include "Asteroid.h"
#include "Component.h"
#include "ObjectPool.h"

class AsteroidsPool : public Component
{
private:
	const int ASTEROID_GENERATION_OFFSET = 50;

	int activeAsteroidsCount_;
	ObjectPool<Asteroid, 30> asteroidsPool_ = ObjectPool<Asteroid, 30>(&Asteroid::getActive);

public:
	AsteroidsPool();
	virtual ~AsteroidsPool();

	inline int getNumOfAsteroids() const { return activeAsteroidsCount_; }

	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);
	const std::vector<Asteroid*>& getPool();

private:
	Vector2D randomPosition();
	Vector2D randomVelocity(const Vector2D& pos);
};

#endif // !__ASTEROIDS_POOL_H__

