#ifndef __GAME_STATE_MACHINE_H__
#define __GAME_STATE_MACHINE_H__

#include <stack>

#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void pushState(GameState* newState);
	void changeState(GameState* newState);
	void popState();

	void handleEvents(SDL_Event& event);
	void update();
	void render();

private:
	std::stack<GameState*> gameStates_;

};

#endif // !__GAME_STATE_MACHINE_H__
