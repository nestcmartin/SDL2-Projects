#include <cmath>

#include "Entity.h"
#include "GhostsPool.h"
#include "EntityManager.h"

#include "Transform.h"
#include "GameState.h"

#include "GhostsSystem.h"
#include "GameCtrlSystem.h"

#include "SDL_macros.h"

#include "SDLGame.h"


GhostsSystem::GhostsSystem() :
	System(ECS::_sys_Ghosts),
	lastTimeAdded_(0), 
	maxGhosts_(10), 
	numOfGhosts_(0) 
{
}

void GhostsSystem::init() 
{
}

void GhostsSystem::update() 
{
	auto gameState = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);
	if (gameState->state_ != GameState::RUNNING) return;

	// Add 2 ghosts every 5sec
	if (lastTimeAdded_ + 5000 < game_->getTime()) 
	{
		lastTimeAdded_ = game_->getTime();
		addGhosts(2);
	}

	for (auto& e : enityManager_->getGroup(ECS::_grp_Ghost)) 
	{
		if (!e->isActive()) return;

		Transform* tr = e->getComponent<Transform>(ECS::Transform);

		// With probability 5% change direction to follow pacman
		RandomNumberGenerator* r = game_->getRandGen();
		if (r->nextInt(0, 100) < 5) 
		{
			Vector2D pmanPositon = enityManager_->getHandler(ECS::_hdlr_PacManEntity)->getComponent<Transform>(ECS::Transform)->position_;
			tr->velocity_ = (pmanPositon - tr->position_).normalize() * (r->nextInt(1, 10) / 20.0);
		}

		// Bounce on borders
		tr->position_ = tr->position_ + tr->velocity_;
		int x = tr->position_.getX();
		int y = tr->position_.getY();

		if (x <= 0 || x + tr->width_ >= game_->getWindowWidth() || 
			y <= 0 || y + tr->height_ >= game_->getWindowHeight()) 
		{
			tr->velocity_ = tr->velocity_.rotate(180);
		}
	}
}

void GhostsSystem::onCollisionWithPacMan(Entity* e) 
{
	enityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->onPacManDeath();
}

void GhostsSystem::addGhosts(std::size_t n) 
{
	// We cannot exceed the maximum number of ghosts
	if (numOfGhosts_ >= maxGhosts_) return;

	RandomNumberGenerator* r = game_->getRandGen();

	Vector2D pacmanPositon = enityManager_->getHandler(ECS::_hdlr_PacManEntity)->getComponent<Transform>(ECS::Transform)->position_;

	// Ghost width and height
	int width = 30;
	int height = 30;

	for (auto i(0u); i < n; i++) 
	{
		// Select corner
		int x = 0;
		int y = 0;

		int c = r->nextInt(0, 4);

		switch (c) 
		{
		case 0:
			x = 10;
			y = 10;
			break;

		case 1:
			x = game_->getWindowWidth() - width - 10;
			y = 10;
			break;

		case 2:
			x = game_->getWindowWidth() - width - 10;
			y = game_->getWindowHeight() - height - 10;
			break;

		case 3:
			x = 10;
			y = game_->getWindowHeight() - height - 10;
			break;
		}

		Vector2D p(x, y);
		Vector2D v = (pacmanPositon - p).normalize() * (r->nextInt(1, 10) / 20.0);

		// Add the entity
		Entity* e = enityManager_->addEntity<GhostsPool>(p, v, 30, 30);
		if (e != nullptr) 
		{
			e->addToGroup(ECS::_grp_Ghost);
			numOfGhosts_++;
		}
	}
}

void GhostsSystem::disableAll() 
{
	for (auto& e : enityManager_->getGroup(ECS::_grp_Ghost)) 
	{
		e->setActive(false);
	}
	numOfGhosts_ = 0;
}
