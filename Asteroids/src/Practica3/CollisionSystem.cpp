#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "EntityManager.h"

CollisionSystem::CollisionSystem() :
	System(ECS::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	auto gameCtrlSys = manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING || manager_->getClientId() != 0)
		return;


	bool roundOver = false;

	for (auto& f : manager_->getGroupEntities(ECS::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ECS::Transform);

		for (auto& b : manager_->getGroupEntities(ECS::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ECS::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
				bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
				fTR->height_, fTR->rotation_)) {

				roundOver = true;
				auto id = f->getComponent<FighterInfo>(ECS::FighterInfo)->fighterId_;
				manager_->send<messages::BulletCollision>(id);
			}
		}
	}

	if (roundOver)
		manager_->getSystem<BulletsSystem>(ECS::_sys_Bullets)->disableAll();
}

