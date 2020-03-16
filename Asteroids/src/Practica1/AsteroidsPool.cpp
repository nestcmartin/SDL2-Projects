#include "AsteroidsPool.h"
#include "SRandBasedGenerator.h"
#include "RandomNumberGenerator.h"

AsteroidsPool::AsteroidsPool() :
	Component(ECS::AsteroidsPool)
{
}

AsteroidsPool::~AsteroidsPool()
{
}

void AsteroidsPool::generateAsteroids(int n)
{
	for (int i = 0; i < n; i++)
	{
		Asteroid* a = asteroidsPool_.getObj();

		if (a)
		{
			RandomNumberGenerator* rnd = game_->getRandomGenerator();

			a->setPos(randomPosition());
			a->setVel(randomVelocity(a->getPos()));
			a->setGenerations(rnd->nextInt(1, 4));
			a->setWH((3 * a->getGenerations()) + 10, (3 * a->getGenerations()) + 10);
			a->setActive(true);
			activeAsteroidsCount_++;
		}
	}
}

void AsteroidsPool::disableAll()
{
	std::vector<Asteroid*> asteroids = getPool();
	for (Asteroid* a : asteroids)
	{
		if (a->getActive())
		{
			a->setActive(false);
			activeAsteroidsCount_--;
		}
	}
}

void AsteroidsPool::onCollision(Asteroid* a, Bullet* b)
{
	a->setActive(false);
	activeAsteroidsCount_--;

	int g = a->getGenerations();
	if (g <= 0) return;

	Vector2D pos = a->getPos();
	Vector2D vel = a->getVel();
	g--;

	for (int i = 0; i < 2; i++)
	{
		Asteroid* asteroid = asteroidsPool_.getObj();

		if (asteroid)
		{
			Vector2D v = vel.rotate(i * 45);
			Vector2D p = pos + v.normalize();

			asteroid->setPos(p);
			asteroid->setVel(v);
			asteroid->setGenerations(g);
			asteroid->setWH(3 * g + 10, 3 * g + 10);
			asteroid->setActive(true);
			activeAsteroidsCount_++;
		}
	}
}

const std::vector<Asteroid*>& AsteroidsPool::getPool()
{
	return asteroidsPool_.getPool();
}

Vector2D AsteroidsPool::randomPosition()
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

Vector2D AsteroidsPool::randomVelocity(const Vector2D& pos)
{
	RandomNumberGenerator* rnd = game_->getRandomGenerator();

	Vector2D c = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	Vector2D r = Vector2D(rnd->nextInt(-ASTEROID_GENERATION_OFFSET, ASTEROID_GENERATION_OFFSET), rnd->nextInt(-ASTEROID_GENERATION_OFFSET, ASTEROID_GENERATION_OFFSET));

	return ((c + r) - pos).normalize() * (rnd->nextInt(1, 11) / 10.0);
}
