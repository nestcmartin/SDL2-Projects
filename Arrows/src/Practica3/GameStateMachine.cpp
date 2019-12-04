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
	popState();
	pushState(newState);
}

void GameStateMachine::popState()
{
	if (!gameStates_.empty())
	{
		if (gameStates_.top()->onExit())
		{
			delete gameStates_.top();
			gameStates_.top() = nullptr;
			gameStates_.pop();
		}
	}
}

void GameStateMachine::handleEvents(SDL_Event& event)
{
	if (!gameStates_.empty())
	{
		gameStates_.top()->handleEvents(event);
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