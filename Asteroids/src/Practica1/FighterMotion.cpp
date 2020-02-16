#include "FighterMotion.h"
#include "Entity.h"

FighterMotion::FighterMotion() :
	Component(ECS::FighterMotion),
	transform_(nullptr)
{
}

FighterMotion::~FighterMotion()
{
}

void FighterMotion::init()
{
	transform_ = GETCMP1_(Transform);
}

void FighterMotion::update()
{
	Vector2D newPos = transform_->getPos() + transform_->getVel() * STOP_FACTOR;
	if (newPos.getX() < 0 || newPos.getX() >= game_->getWindowWidth() - transform_->getW() || 
		newPos.getY() < 0 || newPos.getY() >= game_->getWindowHeight() - transform_->getH()) 
		transform_->setVel(transform_->getVel() * -1);
	transform_->setPos(transform_->getPos() + transform_->getVel() * STOP_FACTOR);
}
