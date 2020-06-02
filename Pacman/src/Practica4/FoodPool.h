#ifndef __FOOD_POOL_H__
#define __FOOD_POOL_H__

#include "Entity.h"
#include "ObjectPool.h"

#include "AnimatedImage.h"
#include "Transform.h"

#include "Singleton.h"

#include "ECS.h"


class FoodPool : public Singleton<FoodPool>
{
	friend Singleton<FoodPool>;

private:
	ObjectPool<Entity> pool_;

public:
	virtual ~FoodPool()
	{
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args)
	{
		return FoodPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p)
	{
		FoodPool::instance()->destroy_(p);
	}

	inline Entity* construct_(const Vector2D& p, double w, double h)
	{
		Entity* e = pool_.getObject();
		if (e != nullptr)
		{
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>(ECS::Transform);
			tr->position_ = p;
			tr->width_ = w;
			tr->height_ = h;
		}
		return e;
	}

	inline void destroy_(Entity* p)
	{
		pool_.releaseObject(p);
	}

private:
	FoodPool() :
		FoodPool(10) 
	{
	}

	FoodPool(std::size_t n) :
		pool_(n) 
	{
		for (Entity* e : pool_.getPool()) 
		{
			e->addComponent<Transform>();
			auto animatedImage = e->addComponent<AnimatedImage>();
			animatedImage->setSpriteTime(100);
			Texture* spritesTex = SDLGame::instance()->getTextureManager()->getTexture(Resources::PacManSprites);
			animatedImage->addSprite(spritesTex, { 128 * 4, 128, 128, 128 });
		}

	}
};

#endif // !__FOOD_POOL_H__