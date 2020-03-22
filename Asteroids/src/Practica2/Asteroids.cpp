#include "ObjectFactory.h"
#include "AsteroidsPool.h"
#include "BulletsPool.h"

#include "SDL_Macros.h"

#include "Asteroids.h"

Asteroids::Asteroids() :
	exit_(false),
	game_(nullptr), 
	entityManager_(nullptr)
{
	initGame();
}

Asteroids::~Asteroids() 
{
	closeGame();
}

void Asteroids::initGame() 
{
	// Inicializamos SDLGame
	game_ = SDLGame::init("Asteroids", WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// Inicializamos los pools y factorías
	ObjectFactory<Entity>::init(50);
	ObjectFactory<Transform>::init(50);
	ObjectFactory<ImageComponent>::init(100);
	ObjectFactory<Rotation>::init(30);
	ObjectFactory<AsteroidLifeTime>::init(30);
	ObjectFactory<Health>::init(1);
	ObjectFactory<Score>::init(1);
	ObjectFactory<GameState>::init(1);
	AsteroidsPool::init(30);
	BulletsPool::init(10);

	// Inicializamos el EntityManager
	entityManager_ = new EntityManager(game_);

	// Inicializamos todos los sistemas
	renderSystem_ = entityManager_->addSystem<RenderSystem>();
	asteroidsSystem_ = entityManager_->addSystem<AsteroidsSystem>();
	bulletSystem_ = entityManager_->addSystem<BulletsSystem>();
	fighterSystem_ = entityManager_->addSystem<FighterSystem>();
	fighterGunSystem_ = entityManager_->addSystem<FighterGunSystem>();
	collisionSystem_ = entityManager_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = entityManager_->addSystem<GameCtrlSystem>();
}

void Asteroids::closeGame() 
{
	delete entityManager_;
}

void Asteroids::start() 
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
		asteroidsSystem_->update();
		bulletSystem_->update();
		fighterSystem_->update();
		fighterGunSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
	}
}