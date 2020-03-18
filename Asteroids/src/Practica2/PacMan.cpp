#include <assert.h>

#include "SDL_Macros.h"
#include "PacMan.h"

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"

#include "StarsPool.h"

PacMan::PacMan() :
	game_(nullptr), 
	entityManager_(nullptr), 
	exit_(false) 
{
	initGame();
}

PacMan::~PacMan() 
{
	closeGame();
}

void PacMan::initGame() 
{
	game_ = SDLGame::init("Stars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	StarsPool::init(100);

	entityManager_ = new EntityManager(game_);

	renderSystem_ = entityManager_->addSystem<RenderSystem>();
	starsSystem_ = entityManager_->addSystem<StarsSystem>();
	pacmanSystem_ = entityManager_->addSystem<PacManSystem>();
	collisionSystem_ = entityManager_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = entityManager_->addSystem<GameCtrlSystem>();
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
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		bool foo;
		ih->update(foo);
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
		starsSystem_->update();
		pacmanSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();


		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
	}
}


