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

void FoodSystem::receive(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_GAME_START:
		addFood(10);
		break;

	case msg::_GAME_OVER:
		disableAll();
		break;

	case msg::_FOOD_COLLISION:
		onEat(static_cast<const msg::FoodCollisionMsg&>(msg).e);
		break;
	}
}

void FoodSystem::onEat(Entity* e) 
{
	// Update score
	auto gameState = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);
	gameState->score_++;

	// Disbale food
	e->setActive(false);
	numOfFoodPieces_--;

	// Game Over
	if (numOfFoodPieces_ == 0)
	{
		enityManager_->send<msg::Message>(msg::_PACMAN_WIN);
	}
}

void FoodSystem::addFood(std::size_t n) 
{
	RandomNumberGenerator* r = game_->getRandomGenerator();

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