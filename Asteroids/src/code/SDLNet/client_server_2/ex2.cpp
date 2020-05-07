#include <iostream>
#include <SDL_net.h>
#include <cstring>

using namespace std;

void error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}

void server(int port) {
	cout << "Starting server at port " << port << endl;
	// some auxiliary variables for sending/receiving information
	char buffer[256];
	int result = 0;

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
	// which means that we want to use 'ip' to start a server
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		error();
	}

	// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
	// a server listening at the port specified in 'ip', and returns a socket for listening
	// to connection requests
	TCPsocket masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		error();
	}

	// We want to use non-blocking communication, the way to do this is via a socket set.
	// We add sockets to this set and then we can ask if any has some activity without blocking.
	// Non-blocking communication is the adequate one for video games!
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1000);

	// add the masterSocket to the set
	SDLNet_TCP_AddSocket(socketSet, masterSocket);

	// an array for clients
	const int MAX_CLIENTS = 10;
	TCPsocket clients[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++) {
		clients[i] = nullptr;
	}

	while (true) {
		// The call to SDLNet_CheckSockets returns the number of sockets with activity
		// in socketSet. The 2nd parameter tells the method to wait up to SDL_MAX_UINT32
		// if there is no activity -- no need to put it 0 unless we really don't want to
		// block. With 0 it would consume CPU unnecessarily
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {

			// if there is an activity in masterSocket we process it. Note that
			// before calling SDLNet_SocketReady we must have called SDLNet_CheckSockets
			if (SDLNet_SocketReady(masterSocket)) {

				// accept the connection (activity on master socket is always a connection
				// request, sending and receiving data is done via the socket returned by
				// SDLNet_TCP_Accept. This way we can serve several clients.
				TCPsocket client = SDLNet_TCP_Accept(masterSocket);

				// look for a free slot
				int j = 0;
				while (j < MAX_CLIENTS && clients[j] != nullptr)
					j++;

				// if there is a slot, add the client to the socketSet and send a connected message,
				// other say we are fully booked and close the connection
				if (j < MAX_CLIENTS) {
					cout << "Client connected, assigned id " << j << endl;
					clients[j] = client;
					SDLNet_TCP_AddSocket(socketSet, client);
					SDLNet_TCP_Send(client, "Connected!", 10);
				} else {
					SDLNet_TCP_Send(client, "Fully booked!", 13);
					SDLNet_TCP_Close(client);
				}
			}

			// check clients activity
			for (int i = 0; i < MAX_CLIENTS; i++) {
				if (clients[i] != nullptr && SDLNet_SocketReady(clients[i])) {
					memset(buffer, 0, 256);
					result = SDLNet_TCP_Recv(clients[i], buffer, 255);

					// if result is zero, then the client has closed the connection
					// and if smaller than zero, then there was some error. In both
					// cases we close the connection
					if (result <= 0) {
						cout << "Client " << i << " disconnected! " << endl;
						SDLNet_TCP_Close(clients[i]);
						SDLNet_TCP_DelSocket(socketSet, clients[i]);
						clients[i] = nullptr;
					} else {
						cout << "Client " << i << " says: " << buffer << endl;
						SDLNet_TCP_Send(clients[i], "Received!", 9);
					}
				}
			}

		}
	}

}

void client(char* host, int port) {

	// some auxiliary variables for sending/receiving information
	char buffer[256];
	int result = 0;

	// a variable that represents the address of the server we want to connect to
	IPaddress ip;

	// fill in the address in 'ip'
	if (SDLNet_ResolveHost(&ip, host, port) < 0) {
		error();
	}

	// establish the connection with the server
	TCPsocket conn = SDLNet_TCP_Open(&ip);
	if (!conn) {
		error();
	}

	// Now we wait for the server's initial message
	// bzero(buffer, 256);
	memset(buffer,0,256);
	result = SDLNet_TCP_Recv(conn, buffer, 255);
	if (result < 0) {
		error(); // something went wrong
	} else if (result == 0) {
		cout << "The server closed the connection without any message!"
				<< endl;
	} else {
		cout << "Server's reply: " << buffer << endl;
	}

	while ( true ) {
		// ask the user for a message
		cout << "Enter a message: ";
		bzero(buffer, 256);
		cin.getline(buffer, 255);

		// exit the loop if the user types exit
		if ( strcmp(buffer,"exit") == 0 )
			break;

		// send the message to the server
		int size = strlen(buffer);
		result = SDLNet_TCP_Send(conn, buffer, size);
		if (result != size) {
			error(); // if send returns a number less than the bytes we have sent then something went wrong
		}

		// Now we wait for the server's response
		bzero(buffer, 256);
		result = SDLNet_TCP_Recv(conn, buffer, 255);
		if (result < 0) {
			error(); // something went wrong
		} else if (result == 0) {
			cout << "The server closed the connection without any message!"
					<< endl;
			break;
		} else {
			cout << "Server's reply: " << buffer << endl;
		}
	}

	// close the connection
	SDLNet_TCP_Close(conn);
}

int main(int argc, char** argv) {

	// initialize SDLNet
	if (SDLNet_Init() < 0) {
		error();
	}

	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	} else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3])); // start in client mode
	} else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
	}

	// finalize SDLNet
	SDLNet_Quit();

	return 0;
}
