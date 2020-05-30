#include <iostream>

#include "StarWars.h"
#include "Networking.h"

void server(int port) {
	Networking net;
	net.server(port);
}

void client(char* host, int port) {
	try {
		StarWars g(host, port);
		g.start();
	}
	catch (std::string & e) { // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception & e) { // catch other exceptions
		cerr << e.what();
	}
	catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

}


int main(int argc, char** argv) {
	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	}
	else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3])); // start in client mode
	}
	else {
		std::cout << "Usage: " << std::endl;
		std::cout << "  " << argv[0] << " client host port " << std::endl;
		std::cout << "  " << argv[0] << " server port " << std::endl;
		std::cout << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "  " << argv[0] << " server 2000" << std::endl;
		std::cout << "  " << argv[0] << " client localhost 2000" << std::endl;
	}

	return 0;
}
