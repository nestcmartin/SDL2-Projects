#include <cassert>
#include <cstdint>

#include "Entity.h"
#include "EntityManager.h"

#include "FighterInfo.h"

#include "GameCtrlSystem.h"
#include "FightersSystem.h"

#include "ECS.h"

using ECS::ComponentId;

GameCtrlSystem::GameCtrlSystem() :
	System(ECS::_sys_GameCtrl) 
{
	state_ = READY;
	resetScore();
}

void GameCtrlSystem::init() 
{
	state_ = READY;
}

void GameCtrlSystem::update() 
{
	if (state_ != RUNNING) 
	{
		InputHandler* ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) startGame();
	}
}

void GameCtrlSystem::startGame() 
{
	if (state_ == GAMEOVER) resetScore();
	entityManager_->getSystem<FightersSystem>(ECS::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) 
{
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter
	state_ = ROUNDOVER;
	
	score[id]++;
	if (score[id] == 3) state_ = GAMEOVER;
}

void GameCtrlSystem::resetScore() 
{
	score[0] = score[1] = 0;
}
