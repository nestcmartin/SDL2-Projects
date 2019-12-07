#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* a) :
	GameState(a)
{
	MenuButton* button = new MenuButton(this, SDLApplication::textures["LOAD"], 200, 80, { 180, 500 }, app_, SDLApplication::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, SDLApplication::textures["PLAY"], 350, 200, { 465, 450 }, app_, SDLApplication::toPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, SDLApplication::textures["EXIT"], 200, 80, { 900, 500 }, app_, SDLApplication::closeApplication);
	addEventHandler(button);
	addGameObject(button);
}

MainMenuState::~MainMenuState()
{
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
	SDLApplication::textures["LOGO"]->render({ 300, 50, 640, 360 });
	GameState::render();
}
