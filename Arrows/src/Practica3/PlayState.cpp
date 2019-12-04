#include "PlayState.h"
#include "SDLApplication.h"

PlayState::PlayState(SDLApplication* a) :
	GameState(a)
{
}

PlayState::~PlayState()
{
}

bool PlayState::onEnter()
{
	return false;
}

bool PlayState::onExit()
{
	return false;
}

void PlayState::handleEvents(SDL_Event& event)
{

}

void PlayState::update()
{
}

void PlayState::render() const
{
}
