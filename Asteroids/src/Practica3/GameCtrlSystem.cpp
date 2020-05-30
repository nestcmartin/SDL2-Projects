#include <cassert>
#include <cstdint>

#include "ECS.h"

#include "Entity.h"
#include "EntityManager.h"

#include "FighterInfo.h"

#include "BulletsSystem.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"


using ECS::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ECS::_sys_GameCtrl) 
{
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::init() 
{
	state_ = WAITING;
	manager_->send<messages::Message>(messages::_PLAYER_INFO);
}

void GameCtrlSystem::update() 
{
	if (state_ != RUNNING && state_ != WAITING)
	{
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) 
		{
			manager_->send<messages::Message>(messages::_START_REQ);
		}
	}
}

void GameCtrlSystem::startGame() 
{
	if (state_ == GAMEOVER) 
	{
		resetScore();
	}

	manager_->getSystem<FightersSystem>(ECS::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) 
{
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;

}

void GameCtrlSystem::resetScore() 
{
	score[0] = score[1] = 0;
}

void GameCtrlSystem::receive(const messages::Message& msg)
{
	switch (msg.id)
	{
	case messages::_PLAYER_INFO:
	{
		if (state_ == READY || msg.senderClientId == manager_->getClientId()) return;

		state_ = READY;
		manager_->send<messages::Message>(messages::_PLAYER_INFO);
		break;
	}

	case messages::_CLIENT_DISCONNECTED: 
	{
		state_ = WAITING;
		resetScore();
		break;
	}

	case messages::_START_REQ: 
	{
		if (manager_->getClientId() == 0 && state_ != RUNNING) 
		{
			manager_->send<messages::Message>(messages::_START_ROUND);
		}
		break;
	}

	case messages::_START_ROUND:
		startGame();
		break;

	case messages::_BULLET_COLLISION:
	{
		onFighterDeath(static_cast<const messages::BulletCollision&>(msg).fighter);
		
		if (manager_->getClientId() != 0)
		{
			manager_->getSystem<BulletsSystem>(ECS::_sys_Bullets)->disableAll();
		}
		break;
	}

	case messages::_FIGHTER_COLLISION:
	{
		state_ = ROUNDOVER;

		if (manager_->getClientId() != 0)
		{
			manager_->getSystem<BulletsSystem>(ECS::_sys_Bullets)->disableAll();
		}
		break;
	}
	}
}
