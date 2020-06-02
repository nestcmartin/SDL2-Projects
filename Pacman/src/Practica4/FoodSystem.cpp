#include "Entity.h"
#include "FoodPool.h"
#include "EntityManager.h"

#include "GameState.h"

#include "System.h"
#include "FoodSystem.h"
#include "GameCtrlSystem.h"

#include "SDL_macros.h"

#include "SDLGame.h"

FoodSystem::FoodSystem() :
	System(ECS::_sys_Food),
	numOfFoodPieces_(0) 
{
}

void FoodSystem::init() 
{
}

void FoodSystem::update() 
{
}

void FoodSystem::onEat(Entity* e) 
{
	// Update score
	auto gameState = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);
	gameState->score_++;

	game_->getAudioMngr()->playChannel(Resources::PacMan_Eat, 0);

	// Disbale food
	e->setActive(false);
	numOfFoodPieces_--;
	if (numOfFoodPieces_ == 0)
	{
		enityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->onNoMoreFood();
	}
}

void FoodSystem::addFood(std::size_t n) 
{
	RandomNumberGenerator* r = game_->getRandGen();

	// Food width and height
	int width = 30;
	int height = 30;

	for (auto i(0u); i < n; i++) 
	{
		int x = r->nextInt(10, game_->getWindowWidth() - width - 10);
		int y = r->nextInt(10, game_->getWindowHeight() - height - 10);
		Vector2D p(x, y);

		// Add the entity
		Entity* e = enityManager_->addEntity<FoodPool>(p, 30, 30);
		if (e != nullptr) 
		{
			e->addToGroup(ECS::_grp_Food);
			numOfFoodPieces_++;
		}
	}
}

void FoodSystem::disableAll() 
{
	for (auto& e : enityManager_->getGroup(ECS::_grp_Food)) 
	{
		e->setActive(false);
	}
	numOfFoodPieces_ = 0;
}