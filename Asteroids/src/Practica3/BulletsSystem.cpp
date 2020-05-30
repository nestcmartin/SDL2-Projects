#include "BulletsSystem.h"
#include "EntityManager.h"
#include "SDLGame.h"
#include "BulletsPool.h"
#include "Transform.h"

BulletsSystem::BulletsSystem() :
		System(ECS::_sys_Bullets) {
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double w, double h) {

	Entity *b = manager_->addEntity<BulletsPool>(pos,vel,w,h);
	if (b != nullptr) {
		b->addToGroup(ECS::_grp_Bullets);
	}
}

void BulletsSystem::disableAll() {
	for (auto &b : manager_->getGroupEntities(ECS::_grp_Bullets))
		b->setActive(false);
}

void BulletsSystem::update() {
	for (auto &e : manager_->getGroupEntities(ECS::_grp_Bullets)) {
		Transform *tr = e->getComponent<Transform>(ECS::Transform);

		Vector2D p = tr->position_ + tr->velocity_;

		if ((p.getX() >= game_->getWindowWidth())
				|| (p.getX() + tr->width_ <= 0)
				|| (p.getY() >= game_->getWindowHeight())
				|| (p.getY() + tr->height_ <= 0)) {
			e->setActive(false);
		} else {
			tr->position_ = p;
		}
	}
}

