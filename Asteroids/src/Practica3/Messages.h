#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace messages {

	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED, 
		_CONNECTION_REFUSED, 
		_CLIENT_DISCONNECTED, 
		_PLAYER_INFO,
		_START_REQ,
		_START_ROUND,
		_BULLET_COLLISION,
		_FIGHTER_INFO,
		_BULLET_INFO,
		_FIGHTER_COLLISION,
		_PLAYER_NAME,

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

	struct ConnectedMsg : Message {
		ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct ClientDisconnectedMsg : Message {
		ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
				clientId) {
		}
		uint32_t clientId;
	};

	struct BulletCollision : Message {
		BulletCollision(uint8_t fighter) :
			Message(sizeof(BulletCollision), _BULLET_COLLISION), fighter(fighter) {
		}
		uint8_t fighter;
	};


	struct FighterInfo : Message {
		FighterInfo(double x, double y, double r) :
			Message(sizeof(FighterInfo), _FIGHTER_INFO), x(x), y(y), r(r) 
		{
		}

		double x;
		double y;
		double r;
	};

	struct BulletInfo : Message {
		BulletInfo(double px, double py, double vx, double vy, double w, double h) :
			Message(sizeof(BulletInfo), _BULLET_INFO), px(px), py(py), vx(vx), vy(vy), w(w), h(h)
		{
		}

		double px;
		double py;
		double vx;
		double vy;
		double w;
		double h;
	};

	struct PlayerName : Message {
		PlayerName(const char* _name) :
			Message(sizeof(PlayerName), _PLAYER_NAME)
		{
			strcpy_s(name, _name);
		}

		char name[11];
	};

#pragma pack(pop)

}

#endif // !__MESSAGES_H__