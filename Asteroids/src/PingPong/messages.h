#pragma once
#include <cstdint>
#include <cstdlib>
#include <ctime>

namespace msg {

using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_CLIENT_DISCONNECTED, //
	_PLAYER_INFO, //
	_PADDLE_INFO, //
	_START_REQ, //
	_START_ROUND, //
	_BALL_SIDE_EXIT_,

	//
	_last_MsgId_
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	uint32_t senderClientId;
	MsgId id;
};

struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
	}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
					clientId) {
	}
	uint32_t clientId;
};

struct PaddleInfoMsg: Message {
	PaddleInfoMsg(double y) :
			Message(sizeof(PaddleInfoMsg), _PADDLE_INFO), y(y) {
	}
	double y;
};


struct StartRoundMsg: Message {
	StartRoundMsg(double x, double y) :
			Message(sizeof(StartRoundMsg), _START_ROUND), x(x), y(y) {
	}
	double x;
	double y;
};

struct BallSideExitMsg: Message {
	BallSideExitMsg(uint8_t side) :
			Message(sizeof(BallSideExitMsg), _BALL_SIDE_EXIT_), side(side) {
	}
	uint8_t side;
};

#pragma pack(pop)

}
