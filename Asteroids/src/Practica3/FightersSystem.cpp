#include "ecs.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Image.h"
#include "CtrlKeys.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"

#include <cstdint>
#include <algorithm>

using ECS::CmpId;

FightersSystem::FightersSystem() :
	System(ECS::_sys_Fighters), 
	fighter0_(nullptr), 
	fighter1_(nullptr) 
{
}

FightersSystem::~FightersSystem() 
{
}

void FightersSystem::resetFighterPositions() 
{
	auto f0Tr = fighter0_->getComponent<Transform>(ECS::Transform);
	f0Tr->velocity_ = Vector2D(0.0, 0.0);
	f0Tr->position_ = Vector2D(10, game_->getWindowHeight() / 2 - 25);
	f0Tr->rotation_ = 90.0;

	auto f1Tr = fighter1_->getComponent<Transform>(ECS::Transform);
	f1Tr->velocity_ = Vector2D(0.0, 0.0);
	f1Tr->position_ = Vector2D(game_->getWindowWidth() - 50.0 - 10.0,
		game_->getWindowHeight() / 2 - 25);
	f1Tr->rotation_ = -90.0;
}

void FightersSystem::receive(const messages::Message& msg)
{
	switch (msg.id)
	{
	case messages::_FIGHTER_INFO:
	{
		if (msg.senderClientId == manager_->getClientId()) return;

		Transform* fighterTR = nullptr;
		if (msg.senderClientId == 0) 
		{
			fighterTR = fighter0_->getComponent<Transform>(ECS::Transform);
		}
		else 
		{
			fighterTR = fighter1_->getComponent<Transform>(ECS::Transform);
		}

		fighterTR->position_.setX(static_cast<const messages::FighterInfo&>(msg).x);
		fighterTR->position_.setY(static_cast<const messages::FighterInfo&>(msg).y);
		fighterTR->rotation_ = static_cast<const messages::FighterInfo&>(msg).r;

		break;
	}
	}
}

void FightersSystem::init() {

	// left fighter
	fighter0_ = manager_->addEntity();
	auto f0Tr = fighter0_->addComponent<Transform>();
	f0Tr->position_ = Vector2D(10, game_->getWindowHeight() / 2 - 25);
	f0Tr->velocity_ = Vector2D(0.0, 0.0);
	f0Tr->width_ = 50.0;
	f0Tr->height_ = 50.0;
	f0Tr->rotation_ = 90.0;
	fighter0_->addComponent<CtrlKeys>(SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN,
		SDLK_SPACE);

	fighter0_->addComponent<Image>(
		game_->getTextureMngr()->getTexture(Resources::Fighter));
	fighter0_->addToGroup(ECS::_grp_Fighters);
	manager_->setHandler(ECS::_hdlr_Fighter0, fighter0_);
	fighter0_->addComponent<FighterInfo>(0);

	// right fighter
	fighter1_ = manager_->addEntity();
	auto f1Tr = fighter1_->addComponent<Transform>();
	f1Tr->position_ = Vector2D(game_->getWindowWidth() - 50.0 - 10.0,
		game_->getWindowHeight() / 2 - 25);
	f1Tr->velocity_ = Vector2D(0.0, 0.0);
	f1Tr->width_ = 50.0;
	f1Tr->height_ = 50.0;
	f1Tr->rotation_ = -90.0;
	fighter1_->addComponent<CtrlKeys>(SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN,
		SDLK_SPACE);

	fighter1_->addComponent<Image>(
		game_->getTextureMngr()->getTexture(Resources::Fighter));
	fighter1_->addToGroup(ECS::_grp_Fighters);
	fighter1_->addComponent<FighterInfo>(1);
	manager_->setHandler(ECS::_hdlr_Fighter1, fighter1_);
}

void FightersSystem::update() {
	auto gameState =
		manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getState();
	if (gameState != GameCtrlSystem::RUNNING)
		return;

	Transform* tr1 = fighter0_->getComponent<Transform>(ECS::Transform);
	Transform* tr2 = fighter1_->getComponent<Transform>(ECS::Transform);

	if (manager_->getClientId() == 0)
	{
		updateFighter(fighter0_);
		manager_->send<messages::FighterInfo>(tr1->position_.getX(), tr1->position_.getY(), tr1->rotation_);
	}
	else
	{
		updateFighter(fighter1_);
		manager_->send<messages::FighterInfo>(tr2->position_.getX(), tr2->position_.getY(), tr2->rotation_);
	}	
}

void FightersSystem::updateFighter(Entity* e) {
	Transform* tr = e->getComponent<Transform>(ECS::Transform);
	CtrlKeys* keys = e->getComponent<CtrlKeys>(ECS::CtrlKeys);

	auto ih = game_->getInputHandler();
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(keys->left_)) { // turn left
			tr->rotation_ = fmod(tr->rotation_ - 5.0, 360.0);
			tr->velocity_ = tr->velocity_.rotate(-5.0);
		}
		else if (ih->isKeyDown(keys->right_)) { // turn right
			tr->rotation_ = fmod(tr->rotation_ + 5.0, 360.0);
			tr->velocity_ = tr->velocity_.rotate(5.0);
		}
		else if (ih->isKeyDown(keys->speedup_)) { // speed up
			tr->velocity_ = Vector2D(0.0, -1.0).rotate(tr->rotation_)
				* (std::min(tr->velocity_.magnitude() + 0.2, 3.0));
		}
		else if (ih->isKeyDown(keys->slowdown_)) { // slow down
			tr->velocity_ = Vector2D(0.0, -1.0).rotate(tr->rotation_)
				* (std::max(tr->velocity_.magnitude() - 0.2, 0.0));
		}
		else if (ih->isKeyDown(keys->shoot_)
			&& game_->getTime() - keys->lastShootTime_ > 1000) { // shoot
			keys->lastShootTime_ = game_->getTime();
			Vector2D p = tr->position_
				+ Vector2D(tr->width_ / 2, tr->height_ / 2)
				+ Vector2D(0, -(tr->height_ / 2 + 5.0)).rotate(
					tr->rotation_);
			Vector2D d = Vector2D(0, -1).rotate(tr->rotation_) * 2;

			manager_->getSystem<BulletsSystem>(ECS::_sys_Bullets)->shoot(p, d, 2, 5);
			manager_->send<messages::BulletInfo>(p.getX(), p.getY(), d.getX(), d.getY(), 2, 5);

		}
	}

	// motion
	Vector2D oldPos = tr->position_;
	Vector2D newPos = tr->position_ + tr->velocity_;

	tr->position_ = newPos;
	tr->velocity_ = tr->velocity_ * 0.995;

	double y = newPos.getY();
	double x = newPos.getX();

	if (y <= 0 || y + tr->height_ >= game_->getWindowHeight() || x <= 0
		|| x + tr->width_ >= game_->getWindowWidth()) {
		tr->velocity_ = Vector2D();
		tr->position_ = oldPos;
	}
}
