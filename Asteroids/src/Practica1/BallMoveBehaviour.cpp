#include "BallMoveBehaviour.h"
#include "Entity.h"

BallMoveBehaviour::BallMoveBehaviour() :
		Component(ecs::BallMoveBehaviour), //
		tr_(nullptr) //
{
}

BallMoveBehaviour::~BallMoveBehaviour() {
}

void BallMoveBehaviour::init() {
	tr_ = GETCMP2_(ecs::Transform, Transform);
}

void BallMoveBehaviour::update() {

	tr_->setPos(tr_->getPos() + tr_->getVel());

	double y = tr_->getPos().getY();

	if (y <= 0 || y + tr_->getH() >= game_->getWindowHeight()) {
		tr_->setVelY(-tr_->getVel().getY());
		game_->getAudioMngr()->playChannel(Resources::Wall_Hit, 0);
	}
}

