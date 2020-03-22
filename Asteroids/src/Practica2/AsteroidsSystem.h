#ifndef __ASTEROIDS_SYSTEM_H__
#define __ASTEROIDS_SYSTEM_H__

#include "Entity.h"
#include "EntityManager.h"
#include "AsteroidsPool.h"

#include "Score.h"
#include "Rotation.h"
#include "Transform.h"
#include "AsteroidLifeTime.h"

#include "System.h"

#include "SDL_Macros.h"

#include "SDLGame.h"

class AsteroidsSystem : public System
{
private:
	std::size_t numOfAsteroids_ = 0;

public:
	void addAsteroids(int n)
	{
		numOfAsteroids_ = 0;

		for (int i = 0; i < n; i++)
		{
			RandomNumberGenerator* rnd = game_->getRandomGenerator();

			Vector2D p = randomPosition();
			Vector2D v = randomVelocity(p);
			int g = rnd->nextInt(1, 4);
			double w = (3 * g) + 10;
			double h = (3 * g) + 10;

			Entity* e = entityManager_->addEntity<AsteroidsPool>(p, v, w, h, 0, g);
			if (!e) return;

			e->addToGroup<_grp_Asteroid>();
			e->setActive(true);
			numOfAsteroids_++;
		}
	}

	void onCollisionWithBullet(Entity* a, Entity* b)
	{
		entityManager_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_++;

		a->setActive(false);
		numOfAsteroids_--;

		Transform* tr = a->getComponent<Transform>();
		double r = a->getComponent<Rotation>()->rotation_;
		int g = a->getComponent<AsteroidLifeTime>()->numGenerations_;
		if (g <= 0) return;

		Vector2D pos = tr->position_;
		Vector2D vel = tr->velocity_;
		g--;

		for (int i = 0; i < 2; i++)
		{
			Vector2D v = vel.rotate(i * 45);
			Vector2D p = pos + v.normalize();
			double w = (3 * g) + 10;
			double h = (3 * g) + 10;

			Entity* e = entityManager_->addEntity<AsteroidsPool>(p, v, w, h, r, g);
			if (!e) return;

			e->addToGroup<_grp_Asteroid>();
			e->setActive(true);
			numOfAsteroids_++;
		}
	}

	void update() override
	{
		if (!entityManager_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->running_) return;

		for (auto& e : entityManager_->getGroupEntities<_grp_Asteroid>())
		{
			if (!e->isActive()) return;

			Transform* tr = e->getComponent<Transform>();
			Vector2D newPos = tr->position_ + tr->velocity_;
			tr->rotation_ += e->getComponent<Rotation>()->rotation_;

			if (newPos.getX() < 0) newPos.setX(game_->getWindowWidth());
			else if (newPos.getX() >= game_->getWindowWidth()) newPos.setX(0);
			if (newPos.getY() < 0) newPos.setY(game_->getWindowHeight());
			else if (newPos.getY() >= game_->getWindowHeight()) newPos.setY(0);

			tr->position_ = newPos;
		}
	}

	bool asteroidsLeft()
	{
		return numOfAsteroids_ > 0;
	}


private:
	Vector2D randomPosition()
	{
		RandomNumberGenerator* rnd = game_->getRandomGenerator();

		double rnd_px = 0;
		double rnd_py = 0;

		// Arriba o abajo
		if (rnd->nextInt(0, 2))
		{
			rnd_px = rnd->nextInt(0, (int)(game_->getWindowWidth()));
			if (rnd->nextInt(0, 2)) rnd_py = 0;
			else rnd_py = game_->getWindowHeight();
		}
		// Izquierda o derecha
		else
		{
			rnd_py = rnd->nextInt(0, (int)(game_->getWindowHeight()));
			if (rnd->nextInt(0, 2)) rnd_px = 0;
			else rnd_px = game_->getWindowWidth();
		}

		return Vector2D(rnd_px, rnd_py);
	}

	Vector2D randomVelocity(const Vector2D& pos)
	{
		RandomNumberGenerator* rnd = game_->getRandomGenerator();

		Vector2D c = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		Vector2D r = Vector2D(rnd->nextInt(-50, 50), rnd->nextInt(-50, 50));

		return ((c + r) - pos).normalize() * (rnd->nextInt(1, 11) / 10.0);
	}
};

#endif // !__ASTEROIDS_SYSTEM_H__