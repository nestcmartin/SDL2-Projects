#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <cstdint>

#include "Component.h"

struct GameState : Component 
{
	enum State : uint8_t 
	{ 
		READY, 
		RUNNING, 
		OVER 
	};

	GameState() :
		Component(ECS::GameState),
		state_(READY),
		won_(false),
		score_(0)
	{
	}

	State state_;
	bool won_;
	int score_;
};

#endif // !__GAME_STATE_H__