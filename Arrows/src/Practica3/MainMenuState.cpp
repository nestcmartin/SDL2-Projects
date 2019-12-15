#include "MainMenuState.h"
#include "SDLApplication.h"
#include "MenuButton.h"

MainMenuState::MainMenuState(SDLApplication* a) :
	GameState(a)
{
	MenuButton* button = new MenuButton(this, app_->getTexture("LOAD"), 200, 80, { 180, 480 }, SDLApplication::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, app_->getTexture("PLAY"), 350, 200, { 465, 430 }, SDLApplication::toPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, app_->getTexture("EXIT"), 200, 80, { 900, 480 }, SDLApplication::closeApplication);
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
	app_->getTexture("LOGO")->render({ 320, 30, (int)app_->getTexture("LOGO")->getWidth(), (int)app_->getTexture("LOGO")->getHeight() });

	int w, h;
	Texture* t = new Texture(app_->getRenderer(), "Nestor Cabrero", app_->getFont("PAINT22"), { 0, 0, 0, 255 });
	app_->getFont("PAINT22")->sizeOfText("Nestor Cabrero", w, h);
	t->render({ int(WIN_WIDTH - w - 10), int(WIN_HEIGHT - h - 10), w, h });
	delete t; t = nullptr;

	GameState::render();
}
