#include <assert.h>

#include "SDL_Macros.h"
#include "Asteroids.h"

// Aquí hay que incluir todos los componentes que se usen
#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "Rectangle.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "Transform.h"

Asteroids::Asteroids() :
	game_(nullptr),
	entityManager_(nullptr),
	exit_(false) 
{
	initGame();
}

Asteroids::~Asteroids() 
{
	closeGame();
}

void Asteroids::initGame() 
{
	// Game + ECS
	game_ = SDLGame::init("Asteroids 1.0", WINDOW_WIDTH, WINDOW_HEIGHT);
	entityManager_ = new EntityManager(game_);

	//// EJEMPLO: Crear Entidad + Agregar Componentes
	// Entity* e = entityManager_->addEntity();
	// Transform* eTransform = e->addComponent<Transform>();
	// e->addComponent<Component1>();
	// e->addComponent<Component2>();
	// eTransform->setPos(game_->getWindowHeight() / 2 - 5, game_->getWindowHeight() / 2 - 25);
	// eTransform->setWH(10, 50);
	
	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>();
	gameManager->addComponent<GameLogic>();
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>();
}

void Asteroids::closeGame() 
{
	delete entityManager_;
}

void Asteroids::run() 
{
	// Bucle principal
	exit_ = false;
	while (!exit_) 
	{
		Uint32 startTime = game_->getCurrentTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getCurrentTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() 
{
	exit_ = true;
}

void Asteroids::handleInput() 
{
	InputHandler* ih = InputHandler::instance();

	ih->update(exit_);

	if (ih->keyDownEvent()) 
	{
		if (ih->isKeyDown(SDLK_ESCAPE)) 
		{
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) 
		{
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) 
			{
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else 
			{
				SDL_SetWindowFullscreen(game_->getWindow(), SDL_WINDOW_FULLSCREEN);
			}
		}
	}
}

void Asteroids::update() 
{
	entityManager_->update();
}

void Asteroids::render() 
{
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());
	entityManager_->draw();
	SDL_RenderPresent(game_->getRenderer());
}