#include "ScoreBoard.h"
#include "GameState.h"
#include "SDLApplication.h"

ScoreBoard::ScoreBoard(SDLApplication* a, Texture* arrowTexture, Texture* digitsTexture) :
	GameObject(),
	app_(a),
	arrowsSprite_(arrowTexture),
	digitsSprite_(digitsTexture),
	arrowsLeft_(NUM_ARROWS),
	score_(0)
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::update()
{
}

void ScoreBoard::render() const
{
	for (int i = 0; i < arrowsLeft_; i++)
	{
		arrowsSprite_->render({ static_cast<int>(UI_ARROW_POS_X + (UI_ARROW_WIDTH * i)),
							   static_cast<int>(UI_ARROW_POS_Y),
							   UI_ARROW_WIDTH, UI_ARROW_HEIGHT });
	}

	int w, h;
	Texture* t = new Texture(app_->getRenderer(), std::to_string(score_), app_->getFont("PAINT72"), { 255, 255, 255, 255 });
	app_->getFont("PAINT72")->sizeOfText(std::to_string(score_), w, h);
	t->render({ UI_SCORE_POS_X, UI_SCORE_POS_Y, w, h });
	delete t; t = nullptr;
}
