#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic() :
	Component(ECS::GameLogic), 
	asteroidsPool_(nullptr),
	bulletsPool_(nullptr), 
	health_(nullptr),
	fighterTransform_(nullptr),
	scoreManager_(nullptr)
{
}

GameLogic::GameLogic(AsteroidsPool* apool, BulletsPool* bpool, Health* health, Transform* fightertr) :
	Component(ECS::GameLogic),
	asteroidsPool_(apool),
	bulletsPool_(bpool),
	health_(health),
	fighterTransform_(fightertr),
	scoreManager_(nullptr)
{
}

GameLogic::~GameLogic() 
{
}

void GameLogic::init() 
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update()
{
	if (scoreManager_->isRunning() && !scoreManager_->isGameOver())
	{
		std::vector<Asteroid*> asteroids = asteroidsPool_->getPool();
		std::vector<Bullet*> bullets = bulletsPool_->getPool();

		for (Asteroid* a : asteroids)
		{
			if (a->getActive())
			{
				// Comprobación de colisiones entre Asteroid y Fighter
				if (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRot(), 
					fighterTransform_->getPos(), fighterTransform_->getW(), fighterTransform_->getH(), fighterTransform_->getRot()))
				{
					game_->getAudioManager()->haltMusic();
					game_->getAudioManager()->playChannel(Resources::ExplosionSound, 0);

					asteroidsPool_->disableAll();
					bulletsPool_->disableAll();
					health_->loseHealth();

					scoreManager_->setRunning(false);
					if (health_->getLives() <= 0)
					{
						scoreManager_->setGameOver(true);
						scoreManager_->setWin(false);

						game_->getAudioManager()->playMusic(Resources::Boooo, 0);
					}

					fighterTransform_->setPos((game_->getWindowWidth() / 2) - 26, (game_->getWindowHeight() / 2) - 37);
					fighterTransform_->setVel(Vector2D(0, 0));
					fighterTransform_->setRot(0);
				}

				// Comprobación de colisiones entre Asteroid y Bullets
				for (Bullet* b : bullets)
				{
					if (b->getActive())
					{
						if (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRot(),
							b->getPos(), b->getW(), b->getH(), b->getRot()))
						{
							game_->getAudioManager()->playChannel(Resources::ExplosionSound, 0);

							asteroidsPool_->onCollision(a, b);
							bulletsPool_->onCollision(b, a);

							scoreManager_->setScore(scoreManager_->getScore() + 1);

							if (asteroidsPool_->getNumOfAsteroids() <= 0)
							{
								scoreManager_->setRunning(false);
								scoreManager_->setGameOver(true);
								scoreManager_->setWin(true);

								asteroidsPool_->disableAll();
								bulletsPool_->disableAll();

								fighterTransform_->setPos((game_->getWindowWidth() / 2) - 26, (game_->getWindowHeight() / 2) - 37);
								fighterTransform_->setVel(Vector2D(0, 0));
								fighterTransform_->setRot(0);

								game_->getAudioManager()->haltMusic();
								game_->getAudioManager()->playMusic(Resources::Cheer, 0);
							}
						}
					}
				}
			}
		}
	}
}