#include "GameCtrl.h"

#include "Entity.h"
#include "InputHandler.h"

GameCtrl::GameCtrl(Transform *ballTR) :
		Component(ecs::GameCtrl), //
		ballTR_(ballTR), //
		scoreManager_(nullptr) //
{
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameCtrl::update() {

	if (InputHandler::instance()->keyDownEvent()) {
		if (!scoreManager_->isRunning()) {
			RandomNumberGenerator *r = game_->getRandGen();
			scoreManager_->setRunning(true);
			int dx = 1 - 2 * r->nextInt(0, 2); // 1 or -1
			int dy = 1 - 2 * r->nextInt(0, 2); // 1 or -1
			Vector2D v(dx * r->nextInt(6, 7), // 2 to 6
			dy * r->nextInt(2, 7) // 2 to 6
					);
			ballTR_->setVel(v.normalize() * 5);

			// rest the score if the game is over
			if (scoreManager_->isGameOver()) {
				scoreManager_->setLeftScore(0);
				scoreManager_->setRightScore(0);
			}
		}
	}
}

void GameCtrl::draw() {

	if (!scoreManager_->isRunning()) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PresAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (scoreManager_->isGameOver()) {
		Texture *gameOver = game_->getTextureMngr()->getTexture(
				Resources::GameOver);
		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}
