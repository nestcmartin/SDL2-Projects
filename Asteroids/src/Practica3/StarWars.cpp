#include "StarWars.h"

#include <string.h>
#include "BulletsPool.h"
#include "SDL_macros.h"

StarWars::StarWars() :
	host_(nullptr),
	port_(0),
	game_(nullptr),
	manager_(nullptr),
	exit_(false)
{
	initGame("Anonymous");
}

StarWars::StarWars(char* host, int port, char* name) :
	host_(host),
	port_(port),
	game_(nullptr),
	manager_(nullptr),
	exit_(false)
{
	if (!name || (name && std::strlen(name) > 10)) initGame("Anonymous");
	initGame(name);
}

StarWars::~StarWars()
{
	closeGame();
}

void StarWars::initGame(const char* name)
{

	game_ = SDLGame::init("Star Wars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	if (!game_->getNetworking()->client(host_, port_))
		throw "Couldn't connect to server!";

	manager_ = new EntityManager(game_, name);

	BulletsPool::init(100);

	networkingSystem_ = manager_->addSystem<NetworkingSystem>();
	fightersSystem_ = manager_->addSystem<FightersSystem>();
	gameCtrlSystem_ = manager_->addSystem<GameCtrlSystem>();
	bulletsSystem_ = manager_->addSystem<BulletsSystem>();
	collisionSystem_ = manager_->addSystem<CollisionSystem>();
	renderSystem_ = manager_->addSystem<RenderSystem>();

}

void StarWars::closeGame()
{
	delete manager_;
}

void StarWars::start()
{
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_)
	{
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update(exit_);
		if (ih->keyDownEvent())
		{
			if (ih->isKeyDown(SDLK_ESCAPE))
			{
				exit_ = true;
				break;
			}
		}

		manager_->refresh();

		gameCtrlSystem_->update();
		fightersSystem_->update();
		bulletsSystem_->update();
		if (collisionSystem_ != nullptr)
			collisionSystem_->update();
		renderSystem_->update();
		networkingSystem_->update();

		manager_->flushMessages();

		SDL_RenderPresent(game_->getRenderer());
		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

