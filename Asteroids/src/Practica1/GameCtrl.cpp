#include "GameCtrl.h"

#include "Entity.h"
#include "InputHandler.h"

GameCtrl::GameCtrl() :
	Component(ECS::GameCtrl),
	health_(nullptr),
	scoreManager_(nullptr),
	asteroidsPool_(nullptr)
{
}

GameCtrl::GameCtrl(Health* health, AsteroidsPool* pool) :
	Component(ECS::GameCtrl),
	health_(health),
	scoreManager_(nullptr),
	asteroidsPool_(pool)
{
}

GameCtrl::~GameCtrl()
{
}

void GameCtrl::init()
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameCtrl::update()
{
	if (!scoreManager_->isRunning() && !scoreManager_->isGameOver())
	{
		if (InputHandler::instance()->keyUpEvent())
		{
			scoreManager_->setRunning(true);
			if (asteroidsPool_) asteroidsPool_->generateAsteroids(10);
			game_->getAudioManager()->playMusic(Resources::ImperialMarch);
		}
	}
	else if (!scoreManager_->isRunning() && scoreManager_->isGameOver())
	{
		if (InputHandler::instance()->keyUpEvent())
		{
			health_->resetHealth();
			scoreManager_->setScore(0);
			scoreManager_->setRunning(true);
			scoreManager_->setGameOver(false);
			if (asteroidsPool_) asteroidsPool_->generateAsteroids(10);
			game_->getAudioManager()->playMusic(Resources::ImperialMarch);
		}
	}
}

void GameCtrl::draw() 
{
	if (!scoreManager_->isRunning())
	{
		Texture* hitanykey = game_->getTextureManager()->getTexture(Resources::PresAnyKey);
		hitanykey->render(game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2, game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}
}
