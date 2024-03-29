#include "EndState.h"
#include "SDLApplication.h"
#include "MenuButton.h"

EndState::EndState(SDLApplication* a, int score, bool win) :
	GameState(a),
	win_(win),
	finalScore_(score),
	leaderBoard_(nullptr)
{
	MenuButton* button = new MenuButton(this, app_->getTexture("MENU"), 200, 80, { 400, 570 }, SDLApplication::toMenuState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton(this, app_->getTexture("EXIT"), 200, 80, { 680, 570 }, SDLApplication::closeApplication);
	addEventHandler(button);
	addGameObject(button);

	leaderBoard_ = new LeaderBoard(a);

	leaderBoard_->update();
	if (win) leaderBoard_->registerPlayerScore(score);
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
	app_->getTexture("BACKGROUND_AUTUMN")->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	if (win_) app_->getTexture("WIN")->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2) + 20, 450, 200 });
	else app_->getTexture("LOSE")->render({ (WIN_WIDTH / 2) - 225, (WIN_HEIGHT / 2) + 20, 450, 200 });
	app_->getTexture("PANEL")->render({ (WIN_WIDTH / 2) - 165, 20, 330, 350});
	leaderBoard_->render();
	GameState::render();
}
