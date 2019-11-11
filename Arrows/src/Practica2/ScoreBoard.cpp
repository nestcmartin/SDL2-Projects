#include "ScoreBoard.h"
#include "Game.h"

ScoreBoard::ScoreBoard(Game* g, Texture* arrowTexture, Texture* digitsTexture) :
	GameObject(),
	game_(g),
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
	for (Uint32 i = 0; i < arrowsLeft_; i++)
	{
		arrowsSprite_->render({ static_cast<int>(UI_ARROW_POS_X + (UI_ARROW_WIDTH * i)),
							   static_cast<int>(UI_ARROW_POS_Y),
							   UI_ARROW_WIDTH, UI_ARROW_HEIGHT });
	}

	Uint32 centenas = score_ / 100;
	Uint32 decenas = (score_ % 100) / 10;
	Uint32 unidades = (score_ % 10);

	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 0)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, centenas);
	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 1)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, decenas);
	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 2)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, unidades);
}
