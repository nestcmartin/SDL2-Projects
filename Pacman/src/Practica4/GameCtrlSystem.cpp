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
	game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
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
			game_->getAudioMngr()->haltMusic();
			startGame();
			break;

		case GameState::OVER:
			gameState_->state_ = GameState::READY;
			gameState_->score_ = 0;
			gameState_->won_ = false;
			game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
			break;

		default:
			assert(false);
			break;
		}
	}
}

void GameCtrlSystem::onPacManDeath() 
{
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = false;
	enityManager_->getSystem<GhostsSystem>(ECS::_sys_Ghosts)->disableAll();
	enityManager_->getSystem<FoodSystem>(ECS::_sys_Food)->disableAll();
	game_->getAudioMngr()->haltMusic();
	game_->getAudioMngr()->playChannel(Resources::PacMan_Death, 0);
}

void GameCtrlSystem::onNoMoreFood() 
{
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;
	enityManager_->getSystem<GhostsSystem>(ECS::_sys_Ghosts)->disableAll();
	enityManager_->getSystem<FoodSystem>(ECS::_sys_Food)->disableAll();
	game_->getAudioMngr()->haltMusic();
	game_->getAudioMngr()->playChannel(Resources::PacMan_Won, 0);
}

void GameCtrlSystem::startGame() 
{
	enityManager_->getSystem<FoodSystem>(ECS::_sys_Food)->addFood(10);
	enityManager_->getSystem<GhostsSystem>(ECS::_sys_Ghosts)->addGhosts(2);
	enityManager_->getSystem<PacManSystem>(ECS::_sys_PacMan)->resetPacManPosition();
}
