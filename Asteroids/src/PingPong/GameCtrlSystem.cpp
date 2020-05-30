#include "GameCtrlSystem.h"

#include "Manager.h"
#include "Score.h"
#include "GameState.h"
#include "messages.h"
#include "PhysicsSystem.h"

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
}

void GameCtrlSystem::recieve(const msg::Message &msg) {
	switch (msg.id) {
	case msg::_PLAYER_INFO: {
		auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
				GameState>(ecs::GameState);
		if (gameState->ready_ || msg.senderClientId == mngr_->getClientId())
			return;

		gameState->ready_ = true;
		mngr_->send<msg::Message>(msg::_PLAYER_INFO);
		break;
	}
	case msg::_CLIENT_DISCONNECTED: {
		auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
				GameState>(ecs::GameState);
		auto score =
				mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<Score>(
						ecs::Score);
		gameState->ready_ = false;
		gameState->currRound_ = 0;
		score->leftScore_ = score->rightScore_ = 0;
		break;
	}
	case msg::_START_REQ: {
		auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
				GameState>(ecs::GameState);

		if (mngr_->getClientId() == 0 && !gameState->running_) {
			Vector2D v =
					mngr_->getSystem<PhysicsSystem>(ecs::_sys_Physics)->resetBallVelocity();
			mngr_->send<msg::StartRoundMsg>(v.getX(), v.getY());
		}
		break;
	}
	case msg::_START_ROUND:
		startRound();
		break;
	case msg::_BALL_SIDE_EXIT_:
		onBallExit(static_cast<const msg::BallSideExitMsg&>(msg).side);
		break;
	default:
		break;
	}
}

void GameCtrlSystem::init() {

	// create the GameInfo entity
	Entity *gameInfo = mngr_->addEntity();
	gameInfo->addComponent<Score>();
	gameInfo->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameInfo, gameInfo);

	mngr_->send<msg::Message>(msg::_PLAYER_INFO);
}

void GameCtrlSystem::update() {
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
			GameState>(ecs::GameState);

	if (gameState->ready_) {
		if (!gameState->running_) {
			InputHandler *ih = game_->getInputHandler();
			if (ih->keyDownEvent()) {
				mngr_->send<msg::Message>(msg::_START_REQ);
			}
		}
	}
}

void GameCtrlSystem::onBallExit(uint8_t side) {
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
			GameState>(ecs::GameState);

	gameState->running_ = false;

	auto score = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<Score>(
			ecs::Score);
	switch (side) {
	case 0:
		score->rightScore_++;
		break;
	case 1:
		score->leftScore_++;
		break;
	default:
		break;
	}

	mngr_->getSystem<PhysicsSystem>(ecs::_sys_Physics)->resetBallPosition();
}

void GameCtrlSystem::startRound() {
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
			GameState>(ecs::GameState);

	// if game is over, reset score, rounds, etc.
	if (gameState->currRound_ == gameState->maxRounds_) {
		gameState->currRound_ = 0;
		auto score =
				mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<Score>(
						ecs::Score);
		score->leftScore_ = score->rightScore_ = 0;
	}

	gameState->running_ = true;
	gameState->currRound_++;
}

