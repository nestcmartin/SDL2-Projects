#include "EndState.h"
#include "SDLApplication.h"

EndState::EndState(SDLApplication* a) :
	GameState(a)
{
}

EndState::~EndState()
{
}

bool EndState::onEnter()
{
	return false;
}

bool EndState::onExit()
{
	return false;
}

void EndState::handleEvents(SDL_Event& event)
{
}

void EndState::update()
{
}

void EndState::render() const
{
}
