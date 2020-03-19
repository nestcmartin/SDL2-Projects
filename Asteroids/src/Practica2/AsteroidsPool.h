#ifndef __ASTEROIDS_POOL_H__
#define __ASTEROIDS_POOL_H__

#include "Entity.h"

#include "AsteroidLifeTime.h"
#include "Rotation.h"
#include "Transform.h"
#include "ImageComponent.h"

#include "ECS.h"
#include "Singleton.h"
#include "ObjectPool.h"

class AsteroidsPool : public Singleton<AsteroidsPool> 
{
	friend Singleton<AsteroidsPool>;

private:
	ObjectPool<Entity> pool_;

public:
	virtual ~AsteroidsPool() 
	{
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) 
	{
		return AsteroidsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) 
	{
		AsteroidsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double w, double h, double r, int generations)
	{
		Entity* e = pool_.getObject();
		if (e != nullptr) 
		{
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>();
			tr->position_ = pos;
			tr->velocity_ = vel;
			tr->width_ = w;
			tr->height_ = h;
			e->getComponent<Rotation>()->rotation_ = r;
			e->getComponent<AsteroidLifeTime>()->numGenerations_ = generations;
		}
		return e;
	}

	inline void destroy_(Entity* p) 
	{
		pool_.releaseObject(p);
	}

private:
	AsteroidsPool() :
		AsteroidsPool(10) 
	{
	}

	AsteroidsPool(std::size_t n) :
		pool_(n) 
	{
		for (Entity* e : pool_.getPool()) 
		{
			e->addComponent<Transform>();
			e->addComponent<AsteroidLifeTime>(3);
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureManager()->getTexture(Resources::Asteroid));
		}
	}
};



#endif // !__ASTEROIDS_POOL_H__