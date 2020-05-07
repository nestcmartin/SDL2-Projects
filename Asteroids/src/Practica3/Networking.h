#ifndef __NETWORKING_H__
#define __NETWORKING_H__

#include <SDL_net.h>

#include "Messages.h"

class Networking 
{
private:
	TCPsocket sock;
	SDLNet_SocketSet socketSet;

	char buffer[256];
	uint8_t clientId;

public:
	Networking();
	virtual ~Networking();

	inline uint8_t getClientId() { return clientId; }

	// Iniciar servidor
	void server(int port);

	// Iniciar cliente
	bool client(char* host, int port);

	// Cliente: enviar un mensaje
	void send(const MSG::Message& msg) 
	{
		send(msg, sock);
	}

	// Cliente: recibir un mensaje
	MSG::Message* receive() 
	{
		if (SDLNet_CheckSockets(socketSet, 0) > 0 && SDLNet_SocketReady(sock)) return receive(sock);
		else return nullptr;
	}	

private:
	void error();
	void send(const MSG::Message& msg, TCPsocket sock);
	MSG::Message* receive(TCPsocket sock);
};

#endif // !__NETWORKING_H__