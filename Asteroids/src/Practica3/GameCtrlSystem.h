#ifndef __GAME_CTRL_SYSTEM_H__
#define __GAME_CTRL_SYSTEM_H__

#include "EntityManager.h"

#include "System.h"

#include "ECS.h"
#include "SDLGame.h"

class GameCtrlSystem : public System
{
public:
	enum State : uint8_t {
		READY, 
		RUNNING, 
		ROUNDOVER, 
		GAMEOVER
	};

private:
	State state_;
	uint8_t score[2];

public:
	GameCtrlSystem();

	void init() override;
	void update() override;
	void onFighterDeath(uint8_t fighterId);
	
	State getState() 
	{ 
		return state_; 
	}

	uint8_t getScore(uint8_t fighterId) 
	{
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}

private:
	void resetScore();
	void startGame();
	void sendMyInfo();
};

#endif // !__GAME_CTRL_SYSTEM_H__