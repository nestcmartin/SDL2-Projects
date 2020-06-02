#include <assert.h>

#include "FoodPool.h"
#include "GhostsPool.h"

#include "FoodSystem.h"

#include "SDL_Macros.h"
#include "InputHandler.h"

#include "PacMan.h"


PacMan::PacMan() :
	exit_(false),
	game_(nullptr),
	entityManager_(nullptr)
{
	initGame();
}

PacMan::~PacMan() 
{
	closeGame();
}

void PacMan::initGame() 
{
	game_ = SDLGame::init("PacMan", WINDOW_WIDTH, WINDOW_HEIGHT);

	// Initialize the pools
	GhostsPool::init(21);        
	FoodPool::init(22);

	// Create the manager
	entityManager_ = new EntityManager(game_);

	// Create the systems
	ghostsSystem_ = entityManager_->addSystem<GhostsSystem>();
	foodSystem_ = entityManager_->addSystem<FoodSystem>();
	pacmanSystem_ = entityManager_->addSystem<PacManSystem>();
	renderSystem_ = entityManager_->addSystem<RenderSystem>();
	collisionSystem_ = entityManager_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = entityManager_->addSystem<GameCtrlSystem>();
	audioSystem_ = entityManager_->addSystem<AudioSystem>();
}

void PacMan::closeGame() 
{
	delete entityManager_;
}

void PacMan::start() 
{
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) 
	{
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x000000FF));
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

		entityManager_->refresh();

		gameCtrlSystem_->update();
		ghostsSystem_->update();
		pacmanSystem_->update();
		foodSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();
		audioSystem_->update();

		entityManager_->flushMessages();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
	}
}

