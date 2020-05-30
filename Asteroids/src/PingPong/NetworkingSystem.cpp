#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId,
					msg::_PLAYER_INFO);
			break;
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
					static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_PADDLE_INFO:
			mngr_->forwardMsg<msg::PaddleInfoMsg>(msg->senderClientId,
					static_cast<msg::PaddleInfoMsg*>(msg)->y);
			break;
		case msg::_START_REQ:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId,
					msg::_START_REQ);
			break;
		case msg::_START_ROUND: {
			msg::StartRoundMsg *m = static_cast<msg::StartRoundMsg*>(msg);
			mngr_->forwardMsg<msg::StartRoundMsg>(msg->senderClientId, m->x,
					m->y);
			break;
		}
		case msg::_BALL_SIDE_EXIT_:
			mngr_->forwardMsg<msg::BallSideExitMsg>(msg->senderClientId,
					static_cast<msg::BallSideExitMsg*>(msg)->side);
			break;

		default:
			assert(false);
			break;
		}
	}
}
