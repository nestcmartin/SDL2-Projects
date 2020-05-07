#pragma once
#include <cstdint>

// Serialization   :   Struct -> Sequence of Bytes
// DeSerialiazation:   Sequence of Bytes  -> Struct



/*
 * Kinds of messages:
 *
 * M0: S->C : 0 int      // Connected
 * M1: S->C : 1          // Not possible to connect
 * M2: S->C : 2          // Please broadcast state
 * M3: S->C : 3 int      // Client disconnected
 * M4: C->C : 4 int int  // State broadcast
 *
 */


// Big Endian vs Little Endian
//
// x = 259
//
//           big       little
// 13440: 00000000    00000011
// 13441: 00000000    00000001
// 13442: 00000001    00000000
// 13443: 00000011    00000000




using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_BROADCAST_REQUEST, //
	_CLIENT_DISCONNECTED, //
	_CLIENT_STATE
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	MsgId id;
};

struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg),_CONNECTED), clientId(clientId) {
	}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg),_CLIENT_DISCONNECTED), clientId(clientId) {
	}
	uint32_t clientId;
};

struct ClientState: Message {
	ClientState(uint32_t clientId, int32_t state) :
			Message(sizeof(ClientState),_CLIENT_STATE), clientId(clientId), state(state) {
	}
	uint32_t clientId;
	int32_t state;
};

#pragma pack(pop)
