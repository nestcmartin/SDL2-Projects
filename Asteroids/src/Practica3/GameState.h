#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Component.h"

struct GameState : Component
{
	GameState() :
		Component(ECS::GameState),
		running_(false),
		win_(false),
		gameOver_(false)
	{

	}

	bool running_;
	bool win_;
	bool gameOver_;
};

#endif // !__GAME_STATE_H__
