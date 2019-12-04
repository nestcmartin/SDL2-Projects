#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* a) :
	GameState(a)
{
}

PauseState::~PauseState()
{
}

bool PauseState::onEnter()
{
	return false;
}

bool PauseState::onExit()
{
	return false;
}

void PauseState::handleEvents(SDL_Event& event)
{
}

void PauseState::update()
{
}

void PauseState::render() const
{
}
