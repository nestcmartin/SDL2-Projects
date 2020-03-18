#include <iostream>

#include "PacMan.h"
#include "checkML.h"

void start() 
{
	PacMan g;
	g.start();
}

int main(int argc, char** argv) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try 
	{
		start();
	}
	catch (std::string & e) 
	{
		std::cerr << e << std::endl;
	}
	catch (const std::exception & e) 
	{ 
		std::cerr << e.what();
	}
	catch (...) 
	{
		std::cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}