#ifndef __BULLETS_POOL_H__
#define __BULLETS_POOL_H__

#include "Entity.h"
#include "ObjectPool.h"
#include "ObjectFactory.h"

#include "Transform.h"
#include "ImageComponent.h"

#include "Singleton.h"

#include "ECS.h"

class BulletsPool : public Singleton<BulletsPool>
{
	friend Singleton<BulletsPool>;

private:
	ObjectPool<Entity> pool_;

public:
	virtual ~BulletsPool()
	{
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args)
	{
		return BulletsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p)
	{
		BulletsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double w, double h)
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
			tr->rotation_ = Vector2D(0, -1).angle(vel);
		}
		return e;
	}

	inline void destroy_(Entity* p)
	{
		pool_.releaseObject(p);
	}

private:
	BulletsPool() :
		BulletsPool(10)
	{
	}

	BulletsPool(std::size_t n) :
		pool_(n)
	{
		for (Entity* e : pool_.getPool())
		{
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureManager()->getTexture(Resources::Bullet));
		}
	}
};


#endif // !__BULLETS_POOL_H__

