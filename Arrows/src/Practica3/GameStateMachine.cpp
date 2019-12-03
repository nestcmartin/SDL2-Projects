#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}

GameStateMachine::~GameStateMachine()
{
	while (!gameStates_.empty())
	{
		popState();
	}
}

void GameStateMachine::pushState(GameState* newState)
{
	gameStates_.push(newState);
	gameStates_.top()->onEnter();
}

void GameStateMachine::changeState(GameState* newState)
{
	if (!gameStates_.empty())
	{

		if (gameStates_.top()->onExit())
		{
			gameStates_.pop();
		}
	}

	gameStates_.push(newState);
	gameStates_.top()->onEnter();
}

void GameStateMachine::popState()
{
	if (!gameStates_.empty())
	{
		if (gameStates_.top()->onExit())
		{
			gameStates_.pop();
		}
	}
}

void GameStateMachine::handleEvents(SDL_Event& event)
{
	if (!gameStates_.empty())
	{
		gameStates_.top()->handleEvents();
	}
}

void GameStateMachine::update()
{
	if (!gameStates_.empty())
	{
		gameStates_.top()->update();
	}
}

void GameStateMachine::render()
{
	if (!gameStates_.empty())
	{
		gameStates_.top()->render();
	}
}