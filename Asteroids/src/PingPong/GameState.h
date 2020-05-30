#pragma once

#include "GameState.h"
#include "Component.h"

struct GameState: Component {
	GameState() :
			Component(ecs::GameState), //
			ready_(false), //
			running_(false), //
			currRound_(0), //
			maxRounds_(3)
	{
	}

	bool ready_;
	bool running_;
	int currRound_;
	int maxRounds_;
};
