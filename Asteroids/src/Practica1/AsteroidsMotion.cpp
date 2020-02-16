#include "AsteroidsMotion.h"
#include "Entity.h"
#include "Asteroid.h"

AsteroidsMotion::AsteroidsMotion() :
	Component(ECS::AsteroidsMotion),
	asteroidsPool_(nullptr)
{
}

AsteroidsMotion::~AsteroidsMotion()
{
}

void AsteroidsMotion::init()
{
	asteroidsPool_ = GETCMP1_(AsteroidsPool);
}

void AsteroidsMotion::update()
{
	std::vector<Asteroid*> asteroids = asteroidsPool_->getPool();

	for (Asteroid* a : asteroids)
	{
		if (a->getActive())
		{
			a->setRot(a->getRot() + ROTATION_FACTOR);

			Vector2D newPos = a->getPos() + a->getVel();

			if (newPos.getX() < 0) newPos.setX(game_->getWindowWidth());
			else if (newPos.getX() >= game_->getWindowWidth()) newPos.setX(0);
			if (newPos.getY() < 0) newPos.setY(game_->getWindowHeight());
			else if (newPos.getY() >= game_->getWindowHeight()) newPos.setY(0);
			
			a->setPos(newPos);
		}
	}
}
