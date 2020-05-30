#include <iostream>

#include "StarWars.h"
#include "Networking.h"

void server(int port) 
{
	Networking net;
	net.server(port);
}

void client(char* host, int port, char* name) 
{
	try 
	{
		StarWars g(host, port, name);
		g.start();
	}
	catch (std::string & e) 
	{ 
		// catch errors thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const std::exception & e) 
	{ 
		// catch other exceptions
		std::cerr << e.what();
	}
	catch (...) 
	{
		std::cerr << "Caught and exception of unknown type...";
	}
}


int main(int argc, char** argv) 
{
	if (argc == 3 && strcmp(argv[1], "server") == 0) 
	{
		// start in server mode
		server(atoi(argv[2])); 
	}
	else if (argc >= 4 && strcmp(argv[1], "client") == 0) 
	{
		// start in client mode
		if (argc == 4)
		{
			client(argv[2], atoi(argv[3]), nullptr);
		}
		else
		{
			client(argv[2], atoi(argv[3]), argv[4]);
		}
	}
	else 
	{
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
