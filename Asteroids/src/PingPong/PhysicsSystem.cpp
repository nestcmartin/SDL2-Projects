#include "PhysicsSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "Collisions.h"
#include <algorithm>    // std::max, std::min

#include "GameCtrlSystem.h"
#include "GameState.h"
#include "messages.h"

PhysicsSystem::PhysicsSystem() :
		System(ecs::_sys_Physics) {
}

PhysicsSystem::~PhysicsSystem() {
}

void PhysicsSystem::recieve(const msg::Message &msg) {
	switch (msg.id) {
	case msg::_PADDLE_INFO: {
		if (msg.senderClientId == mngr_->getClientId())
			return;

		Transform *paddleTR = nullptr;
		if ( msg.senderClientId == 0 ) {
			paddleTR = mngr_->getHandler(ecs::_hdlr_LeftPaddle)->getComponent<
							Transform>(ecs::Transform);
		} else {
			paddleTR = mngr_->getHandler(ecs::_hdlr_RightPaddle)->getComponent<
							Transform>(ecs::Transform);
		}

		paddleTR->position_.setY( static_cast<const msg::PaddleInfoMsg&>(msg).y);

		break;
	}
	case msg::_START_ROUND: {
		const msg::StartRoundMsg& m = static_cast<const msg::StartRoundMsg&>(msg);
		auto ballTR = mngr_->getHandler(ecs::_hdlr_Ball)->getComponent<Transform>(
				ecs::Transform);
		ballTR->velocity_.set(m.x, m.y);
		break;
	}
	default:
		break;
	}
}

void PhysicsSystem::resetBallPosition() {
	Transform *ballTR = mngr_->getHandler(ecs::_hdlr_Ball)->getComponent<
			Transform>(ecs::Transform);
	ballTR->width_ = 10;
	ballTR->height_ = 10;
	ballTR->position_ = Vector2D((game_->getWindowWidth() - ballTR->width_) / 2,
			(game_->getWindowHeight() - ballTR->height_) / 2);
}

Vector2D PhysicsSystem::resetBallVelocity() {
	RandomNumberGenerator *r = game_->getRandGen();
	int dx = 1 - 2 * r->nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r->nextInt(0, 2); // 1 or -1
	Vector2D v(dx * r->nextInt(6, 7), // 2 to 6
	dy * r->nextInt(2, 7) // 2 to 6
			);
	return v.normalize() * 5;
}

void PhysicsSystem::init() {

	// create ball entity
	Entity *ball = mngr_->addEntity();
	ball->addComponent<Transform>();
	mngr_->setHandler(ecs::_hdlr_Ball, ball);
	resetBallPosition();

	// create left-paddle entity
	Entity *leftPaddle = mngr_->addEntity();
	Transform *leftPaddleTR = leftPaddle->addComponent<Transform>();
	mngr_->setHandler(ecs::_hdlr_LeftPaddle, leftPaddle);
	leftPaddleTR->width_ = 10;
	leftPaddleTR->height_ = 50;
	leftPaddleTR->position_ = Vector2D(10,
			(game_->getWindowHeight() - leftPaddleTR->height_) / 2);

	// create right-paddle entity
	Entity *rightPaddle = mngr_->addEntity();
	Transform *rightPaddleTR = rightPaddle->addComponent<Transform>();
	mngr_->setHandler(ecs::_hdlr_RightPaddle, rightPaddle);
	rightPaddleTR->width_ = 10;
	rightPaddleTR->height_ = 50;
	rightPaddleTR->position_ = Vector2D(
			game_->getWindowWidth() - rightPaddleTR->width_ - 10,
			(game_->getWindowHeight() - leftPaddleTR->height_) / 2);

}

void PhysicsSystem::update() {

	auto gameState = mngr_->getHandler(ecs::GameState)->getComponent<GameState>(
			ecs::GameState);
	bool isGameActive = gameState->running_;

	auto ballTR = mngr_->getHandler(ecs::_hdlr_Ball)->getComponent<Transform>(
			ecs::Transform);

	if (isGameActive) {
		moveBall(ballTR);
		if (mngr_->getClientId() == 0 && checkSidesCollision(ballTR, ballTR, ballTR))
			return;
	}

	auto leftPaddleTR = mngr_->getHandler(ecs::_hdlr_LeftPaddle)->getComponent<
			Transform>(ecs::Transform);

	auto rightPaddleTR =
			mngr_->getHandler(ecs::_hdlr_RightPaddle)->getComponent<Transform>(
					ecs::Transform);

	InputHandler *ih = game_->getInputHandler();

	if (ih->mouseMotionEvent()) {
		if (mngr_->getClientId() == 0)
			movePaddleWithMouse(leftPaddleTR, ih->getMousePos().getY());
		else
			movePaddleWithMouse(rightPaddleTR, ih->getMousePos().getY());
	}

	if (isGameActive) {
		checkBallPaddlesCollision(ballTR, leftPaddleTR, rightPaddleTR);
		checkBottomUpCollision(ballTR, rightPaddleTR, rightPaddleTR);
	}
}

void PhysicsSystem::moveBall(Transform *ballTR) {
	ballTR->position_ = ballTR->position_ + ballTR->velocity_;
}

void PhysicsSystem::movePaddleWithMouse(Transform *p, double mouseYPos) {
	double y = std::min( //
			game_->getWindowHeight() - p->height_, //
			std::max(0.0, mouseYPos) //
					);
	p->position_.setY(y);
	mngr_->send<msg::PaddleInfoMsg>(y);
}

bool PhysicsSystem::checkSidesCollision(Transform *ballTR,
		Transform *leftPaddleTR, Transform *rightPaddleTR) {
	// check if ball exit from sides
	bool collides = false;
	uint8_t side = 0;
	if (ballTR->position_.getX() <= 0) {
		collides = true;
		side = 0;
	} else if (ballTR->position_.getX() + ballTR->width_
			>= game_->getWindowWidth()) {
		collides = true;
		side = 1;
	}

	if ( collides )
		mngr_->send<msg::BallSideExitMsg>(side);

	return collides;

}

bool PhysicsSystem::checkBallPaddlesCollision(Transform *ballTR,
		Transform *leftPaddleTR, Transform *rightPaddleTR) {
	bool collides = false;

	// check collision of paddle with ball
	if (Collisions::collides(ballTR->position_, ballTR->width_, ballTR->height_,
			leftPaddleTR->position_, leftPaddleTR->width_,
			leftPaddleTR->height_)
			|| Collisions::collides(ballTR->position_, ballTR->width_,
					ballTR->height_, rightPaddleTR->position_,
					rightPaddleTR->width_, rightPaddleTR->height_)) {
		ballTR->velocity_.setX(-1 * ballTR->velocity_.getX());
		ballTR->velocity_ = ballTR->velocity_ * 1.2;
		collides = true;
	}

	return collides;
}

bool PhysicsSystem::checkBottomUpCollision(Transform *ballTR,
		Transform *leftPaddleTR, Transform *rightPaddleTR) {
	// ball bounces on top/bottom borders
	bool collides = false;

	if (ballTR->position_.getY() <= 0) {
		ballTR->position_.setY(0);
		ballTR->velocity_.setY(-1 * ballTR->velocity_.getY());
		collides = true;
	} else if (ballTR->position_.getY() + ballTR->height_
			>= game_->getWindowHeight()) {
		ballTR->position_.setY(game_->getWindowHeight() - ballTR->height_);
		ballTR->velocity_.setY(-1 * ballTR->velocity_.getY());
		collides = true;
	}

	return collides;
}
