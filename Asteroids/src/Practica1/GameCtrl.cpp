#include "GameCtrl.h"

#include "Entity.h"
#include "InputHandler.h"


GameCtrl::GameCtrl() :
	Component(ECS::GameCtrl),
	scoreManager_(nullptr)
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
}

void GameCtrl::draw() 
{
	// Mensaje "PRESS ANY KEY"
	if (!scoreManager_->isRunning()) 
	{
		Texture* hitanykey = game_->getTextureManager()->getTexture(Resources::PresAnyKey);
		hitanykey->render(game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2, game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// MENSAJE "GAME OVER"
	if (scoreManager_->isGameOver()) 
	{
		Texture* gameOver = game_->getTextureManager()->getTexture(Resources::GameOver);
		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2, game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}
