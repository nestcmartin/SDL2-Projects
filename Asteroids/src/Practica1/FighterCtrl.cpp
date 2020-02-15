#include "FighterCtrl.h"
#include "Entity.h"
#include "InputHandler.h"


FighterCtrl::FighterCtrl() :
	Component(ECS::FighterCtrl),
	thrustKey_(),
	turnLeftKey_(),
	turnRightKey_(),
	transform_(nullptr)
{
}

FighterCtrl::FighterCtrl(SDL_Keycode up, SDL_Keycode right, SDL_Keycode left) :
	Component(ECS::FighterCtrl),
	thrustKey_(up),
	turnLeftKey_(left),
	turnRightKey_(right),
	transform_(nullptr)
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::init()
{
	transform_ = GETCMP1_(Transform);
}

void FighterCtrl::update()
{
	if (InputHandler::instance()->isKeyDown(turnLeftKey_))
	{
		transform_->setRot(transform_->getRot() + ROTATION_DEGREES);
	}
	else if (InputHandler::instance()->isKeyDown(turnRightKey_))
	{
		transform_->setRot(transform_->getRot() - ROTATION_DEGREES);
	}
	else if (InputHandler::instance()->isKeyDown(thrustKey_))
	{
		Vector2D newVel = transform_->getVel() + Vector2D(0, -1).rotate(transform_->getRot()) * THRUST;
		if (newVel.magnitude() > SPEED_LIMIT) newVel = newVel.normalize() * SPEED_LIMIT;
		transform_->setVel(newVel);
	}
}
