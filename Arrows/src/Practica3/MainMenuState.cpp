#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* a) :
	GameState(a)
{
}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::onEnter()
{
	MenuButton* button = new MenuButton(this, SDLApplication::textures["EXIT"], 200, 80, { 600, 300 }, app_, SDLApplication::closeApplication);
	addEventHandler(button);
	addGameObject(button);
	return true;
}

bool MainMenuState::onExit()
{
	return true;
}

void MainMenuState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::render() const
{
	SDLApplication::textures["BACKGROUND_AUTUMN"]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	GameState::render();
}
