#include "EntityManager.h"

#include "GameState.h"

#include "FoodSystem.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "GameCtrlSystem.h"

#include "SDLGame.h"


GameCtrlSystem::GameCtrlSystem() :
	System(ECS::_sys_GameCtrl),
	gameState_(nullptr) 
{
}

void GameCtrlSystem::init() 
{
	Entity* e = enityManager_->addEntity();
	gameState_ = e->addComponent<GameState>();
	enityManager_->setHandler(ECS::_hdlr_GameStateEntity, e);
}

void GameCtrlSystem::update() 
{
	if (gameState_->state_ == GameState::RUNNING) return;

	auto ih = game_->getInputHandler();

	if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) 
	{
		switch (gameState_->state_) 
		{
		case GameState::READY:
			gameState_->state_ = GameState::RUNNING;
			startGame();
			break;

		case GameState::OVER:
			gameState_->state_ = GameState::READY;
			gameState_->score_ = 0;
			gameState_->won_ = false;
			enityManager_->send<msg::Message>(msg::_RESET);
			break;

		default:
			assert(false);
			break;
		}
	}
}

void GameCtrlSystem::receive(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_PACMAN_WIN:
		onNoMoreFood();
		break;

	case msg::_PACMAN_LOSE:
		onPacManDeath();
		break;
	}
}

void GameCtrlSystem::onPacManDeath() 
{
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = false;

	enityManager_->send<msg::Message>(msg::_GAME_OVER);
}

void GameCtrlSystem::onNoMoreFood() 
{
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;

	enityManager_->send<msg::Message>(msg::_GAME_OVER);
}

void GameCtrlSystem::startGame() 
{
	enityManager_->send<msg::Message>(msg::_GAME_START);
}
