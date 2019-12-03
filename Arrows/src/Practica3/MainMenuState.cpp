#include "MainMenuState.h"

MainMenuState::MainMenuState(SDLApplication* g) :
	GameState(g)
{
}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::onEnter()
{
	return false;
}

bool MainMenuState::onExit()
{
	return false;
}

void MainMenuState::handleEvents(SDL_Event& event)
{
}

void MainMenuState::update()
{
}

void MainMenuState::render() const
{
}
