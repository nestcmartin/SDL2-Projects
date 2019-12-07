#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* a) :
	GameState(a)
{
	MenuButton* button = new MenuButton(this, SDLApplication::textures["SAVE"], 200, 80, { 180, 350 }, app_, SDLApplication::savePlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, SDLApplication::textures["RESUME"], 350, 200, { 465, 300 }, app_, SDLApplication::resumeApplication);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, SDLApplication::textures["EXIT"], 200, 80, { 900, 350 }, app_, SDLApplication::toMenuState);
	addEventHandler(button);
	addGameObject(button);
}

PauseState::~PauseState()
{
}

void PauseState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::render() const
{
	SDLApplication::textures["BACKGROUND_SPRING"]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	GameState::render();
}
