#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic(Transform *ballTR, Transform *leftPaddleTR,
		Transform *rightPaddleTR) :
		Component(ecs::GameLogic), //
		ballTR_(ballTR), //
		leftPaddleTR_(leftPaddleTR), //
		rightPaddleTR_(rightPaddleTR), //
		scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {
	// check for collision of ball with paddles
	if (Collisions::collides(ballTR_->getPos(), ballTR_->getW(),
			ballTR_->getH(), leftPaddleTR_->getPos(), leftPaddleTR_->getW(),
			leftPaddleTR_->getH())
			|| Collisions::collides(ballTR_->getPos(), ballTR_->getW(),
					ballTR_->getH(), rightPaddleTR_->getPos(),
					rightPaddleTR_->getW(), rightPaddleTR_->getH())) {
		Vector2D v = ballTR_->getVel();
		v.setX(-v.getX());
		ballTR_->setVel(v * 1.2);
		game_->getAudioMngr()->playChannel(Resources::Paddle_Hit, 0);
	}

	// check if the back exit from sides
	if (ballTR_->getPos().getX() <= 0) {
		scoreManager_->setRightScore(scoreManager_->getRightScore() + 1);
		scoreManager_->setRunning(false);
		ballTR_->setVel(Vector2D(0, 0));
		ballTR_->setPos(
				Vector2D(game_->getWindowWidth() / 2 - 6,
						game_->getWindowHeight() / 2 - 6));

	} else if (ballTR_->getPos().getX() + ballTR_->getW()
			>= game_->getWindowWidth()) {
		scoreManager_->setLeftScore(scoreManager_->getLeftScore() + 1);
		scoreManager_->setRunning(false);
		ballTR_->setPos(
				Vector2D(game_->getWindowWidth() / 2 - 6,
						game_->getWindowHeight() / 2 - 6));
		ballTR_->setVel(Vector2D(0, 0));
	}
}

