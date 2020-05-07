#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Component.h"

struct GameState : Component
{
	GameState() :
		Component(ECS::GameState),
		running_(false),
		gameOver_(false),
		win_(false)
	{
	}

	bool running_;
	bool gameOver_;
	bool win_;
};


#endif // !__GAME_STATE_H__

