#include "EndState.h"
#include "SDLApplication.h"

EndState::EndState(SDLApplication* a, int score, bool win) :
	GameState(a),
	win_(win),
	finalScore_(score),
	leaderBoard_(nullptr)
{
	MenuButton* button = new MenuButton(this, SDLApplication::textures["PLAY"], 200, 80, { 400, 550 }, app_, SDLApplication::toMenuState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, SDLApplication::textures["EXIT"], 200, 80, { 680, 550 }, app_, SDLApplication::closeApplication);
	addEventHandler(button);
	addGameObject(button);

	leaderBoard_ = new LeaderBoard();

	leaderBoard_->update();
	leaderBoard_->registerPlayerScore(score);
	leaderBoard_->render();
}

EndState::~EndState()
{
	delete leaderBoard_; leaderBoard_ = nullptr;
}

void EndState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}

void EndState::update()
{
	GameState::update();
}

void EndState::render() const
{
	SDLApplication::textures["BACKGROUND_AUTUMN"]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	if (win_) SDLApplication::textures["WIN"]->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2), 450, 200 });
	else SDLApplication::textures["LOSE"]->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2), 450, 200 });
	GameState::render();
}
