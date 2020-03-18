#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "Transform.h"


class StarsPool: public Singleton<StarsPool> {
	friend Singleton<StarsPool> ;
public:
	virtual ~StarsPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs &&...args) {
		return StarsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity *p) {
		StarsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(double x, double y, double w, double h, double r, Uint32 lifeTime) {
		Entity *e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform *tr = e->getComponent<Transform>();
			tr->position_.set(x,y);
			tr->width_ = w;
			tr->height_ = w;
			LifeTime *st = e->getComponent<LifeTime>();
			st->lifeTime_ = lifeTime*1000;
			st->creatiomTime_ = SDLGame::instance()->getTime();
			e->getComponent<Rotation>()->rotation_ = r;
		}
		return e;
	}

	inline void destroy_(Entity *p) {
		pool_.relObj(p);
	}

private:
	StarsPool() :
			StarsPool(10) {
	}
	StarsPool(std::size_t n) :
			pool_(n) {
		for (Entity *e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<LifeTime>();
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Star));
		}
	}

	ObjectPool<Entity> pool_;
};

