#include "ObjectFactory.h"

#include "BulletsPool.h"

#include "SDL_Macros.h"

#include "StarWars.h"

StarWars::StarWars() :
	exit_(false),
	game_(nullptr), 
	entityManager_(nullptr)
{
	initGame();
}

StarWars::~StarWars() 
{
	closeGame();
}

void StarWars::initGame() 
{
	// Inicializamos SDLGame
	game_ = SDLGame::init("Star Wars", WINDOW_WIDTH, WINDOW_HEIGHT);

	// Inicializamos el EntityManager
	entityManager_ = new EntityManager(game_);
	
	// Inicializamos los pools y factorías
	BulletsPool::init(100);

	// Inicializamos todos los sistemas
	fighterSystem_ = entityManager_->addSystem<FightersSystem>();
	gameCtrlSystem_ = entityManager_->addSystem<GameCtrlSystem>();
	bulletSystem_ = entityManager_->addSystem<BulletsSystem>();
	collisionSystem_ = entityManager_->addSystem<CollisionSystem>();
	renderSystem_ = entityManager_->addSystem<RenderSystem>();
}

void StarWars::closeGame() 
{
	delete entityManager_;
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
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_ESCAPE)) exit_ = true;

		entityManager_->refresh();

		gameCtrlSystem_->update();
		fighterSystem_->update();
		bulletSystem_->update();
		if (collisionSystem_) collisionSystem_->update();
		renderSystem_->update();

		entityManager_->flushMessages();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
	}
}