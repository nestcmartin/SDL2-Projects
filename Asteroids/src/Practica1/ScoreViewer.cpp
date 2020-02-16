#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_Macros.h"

ScoreViewer::ScoreViewer() :
	Component(ECS::ScoreViewer),
	scoreManager_(nullptr)
{
}

ScoreViewer::~ScoreViewer()
{
}

void ScoreViewer::init()
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw()
{
	if (scoreManager_->isGameOver())
	{
		Texture* gameOver;

		if (scoreManager_->isWin()) gameOver = game_->getTextureManager()->getTexture(Resources::GameOverWin);
		else gameOver = game_->getTextureManager()->getTexture(Resources::GameOverLose);

		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2, game_->getWindowHeight() - gameOver->getHeight() - 150);
	}

	if (scoreManager_->isGameOver() || scoreManager_->isRunning())
	{
		std::string s = std::to_string(scoreManager_->getScore());
		Texture score(game_->getRenderer(), s, *(game_->getFontManager()->getFont(Resources::ARIAL24)), { COLOR(0x111122ff) });
		score.render(game_->getRenderer(), game_->getWindowWidth() / 2 - score.getWidth() / 2, 10);
	}
}
