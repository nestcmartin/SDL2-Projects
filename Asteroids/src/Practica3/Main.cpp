#include <iostream>

#include "checkML.h"

#include "StarWars.h"

int main(int argc, char** argv) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try 
	{
		StarWars g;
		g.start();
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