#include <time.h>

#include "Game.h"
#include "checkML.h"

int main(int argc, char* argv[]) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned int>(time(NULL)));

	try
	{
		Game* g = new Game();
		g->run();
		delete g;
		g = nullptr;
	}
	catch (SDLError e)
	{
		std::cerr << "SDL exception!\n";
		std::cerr << e.what() << std::endl;
	}
	catch (FileNotFoundError e)
	{
		std::cerr << "File Not Found exception!\n";
		std::cerr << e.what() << std::endl;
	}

	return 0;
}