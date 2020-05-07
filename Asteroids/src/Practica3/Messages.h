#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace MSG 
{
	using msgSizeType = uint32_t;

	enum MsgId : uint8_t 
	{
		_CONNECTED,
		_CONNECTION_REFUSED,
		_CLIENT_DISCONNECTED,

		// YOU SHALL NOT PASS
		_last_MsgId_
	};

#pragma pack(push, 1)

	struct Message 
	{
		Message(msgSizeType size, MsgId id) :
			size(size), 
			senderClientId(0), 
			id(id) 
		{
		}

		Message(MsgId id) :
			Message(sizeof(Message), id) 
		{
		}

		MsgId id;
		msgSizeType size;
		uint32_t senderClientId;
	};

	struct ConnectedMsg : Message 
	{
		ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), 
			clientId(clientId) 
		{
		}

		uint32_t clientId;
	};

	struct ClientDisconnectedMsg : Message 
	{
		ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), 
			clientId(clientId) 
		{
		}

		uint32_t clientId;
	};

#pragma pack(pop)
}

#endif // !__MESSAGES_H__