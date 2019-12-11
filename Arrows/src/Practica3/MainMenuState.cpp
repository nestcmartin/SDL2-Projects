#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* a) :
	GameState(a)
{
	MenuButton* button = new MenuButton(this, app_->getTexture("LOAD"), 200, 80, { 180, 500 }, SDLApplication::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, app_->getTexture("PLAY"), 350, 200, { 465, 450 }, SDLApplication::toPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, app_->getTexture("EXIT"), 200, 80, { 900, 500 }, SDLApplication::closeApplication);
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
	app_->getTexture("BACKGROUND_AUTUMN")->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	app_->getTexture("LOGO")->render({ 300, 50, 640, 360 });
	GameState::render();
}
