#include "EntityManager.h"

#include "Transform.h"
#include "GameState.h"

#include "FoodSystem.h"
#include "GhostsSystem.h"
#include "CollisionSystem.h"

#include "Collisions.h"


CollisionSystem::CollisionSystem() :
	System(ECS::_sys_Collisions) 
{
}

void CollisionSystem::update() 
{
	auto gameState = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);
	if (gameState->state_ != GameState::RUNNING) return;

	auto ptr = enityManager_->getHandler(ECS::_hdlr_PacManEntity)->getComponent<Transform>(ECS::Transform);

	// Collision with food
	for (auto& e : enityManager_->getGroup(ECS::_grp_Food)) 
	{
		auto etr = e->getComponent<Transform>(ECS::Transform);
		
		if (Collisions::collides(
			ptr->position_, ptr->width_, ptr->height_,
			etr->position_, etr->width_, etr->height_)) 
		{
			enityManager_->send<msg::FoodCollisionMsg>(e);
		}
	}

	// Collision with ghosts
	for (auto& e : enityManager_->getGroup(ECS::_grp_Ghost)) 
	{
		auto etr = e->getComponent<Transform>(ECS::Transform);

		if (Collisions::collides(
			ptr->position_, ptr->width_, ptr->height_, 
			etr->position_, etr->width_, etr->height_)) 
		{
			enityManager_->send<msg::GhostCollisionMsg>(e);
			break;
		}
	}
}
