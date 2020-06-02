#ifndef __GHOST_POOL_H__
#define __GHOST_POOL_H__

#include "Entity.h"
#include "ObjectPool.h"

#include "Transform.h"
#include "AnimatedImage.h"

#include "ECS.h"
#include "Singleton.h"


class GhostsPool : public Singleton<GhostsPool>
{
	friend Singleton<GhostsPool>;

private:
	ObjectPool<Entity> pool_;

public:
	virtual ~GhostsPool() 
	{
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) 
	{
		return GhostsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) 
	{
		GhostsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(const Vector2D& p, const Vector2D& v, double w, double h) 
	{
		Entity* e = pool_.getObject();
		if (e != nullptr) 
		{
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>(ECS::Transform);
			tr->position_ = p;
			tr->velocity_ = v;
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
	GhostsPool() :
		GhostsPool(10) 
	{
	}

	GhostsPool(std::size_t n) :
		pool_(n) 
	{
		for (Entity* e : pool_.getPool()) 
		{
			e->addComponent<Transform>();
			auto animatedImage = e->addComponent<AnimatedImage>();
			animatedImage->setSpriteTime(100);
			Texture* spritesTex =SDLGame::instance()->getTextureManager()->getTexture(Resources::PacManSprites);
			
			for (int i = 0; i < 4; i++) 
			{
				animatedImage->addSprite(spritesTex, { i * 128, 768, 128, 128 });
			}

		}

	}
};

#endif // !__GHOST_POOL_H__