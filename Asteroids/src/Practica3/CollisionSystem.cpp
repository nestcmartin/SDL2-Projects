#include "EntityManager.h"

#include "Transform.h"
#include "FighterInfo.h"

#include "BulletsSystem.h"
#include "GameCtrlSystem.h"
#include "CollisionSystem.h"

#include "Collisions.h"

CollisionSystem::CollisionSystem() :
	System(ECS::_sys_Collision) 
{
}

CollisionSystem::~CollisionSystem() 
{
}

void CollisionSystem::update() 
{
	auto gameCtrlSys = entityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl);
	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING) return;

	bool roundOver = false;

	for (auto& f : entityManager_->getGroupEntities(ECS::_grp_Fighters)) 
	{
		auto fTR = f->getComponent<Transform>(ECS::Transform);

		for (auto& b : entityManager_->getGroupEntities(ECS::_grp_Bullets))
		{
			if (!b->isActive()) continue;
			
			auto bTR = b->getComponent<Transform>(ECS::Transform);

			if (Collisions::collidesWithRotation(
				bTR->position_, bTR->width_, bTR->height_, bTR->rotation_, 
				fTR->position_, fTR->width_, fTR->height_, fTR->rotation_)) 
			{

				roundOver = true;
				auto id = f->getComponent<FighterInfo>(ECS::FighterInfo)->fighterId;
				entityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->onFighterDeath(id);
			}
		}
	}

	if (roundOver) entityManager_->getSystem<BulletsSystem>(ECS::_sys_Bullets)->disableAll();
}

