#include "PaddleMoveBehaviour.h"

#include "Entity.h"

PaddleMoveBehaviour::PaddleMoveBehaviour() :
		Component(ecs::PaddleMoveBehaviour), tr_(nullptr) {
}

PaddleMoveBehaviour::~PaddleMoveBehaviour() {
}

void PaddleMoveBehaviour::init() {
	tr_ = GETCMP1_(Transform);
}

void PaddleMoveBehaviour::update() {

	Vector2D v = tr_->getPos() + tr_->getVel();

	double y = v.getY();

	if (y <= 0) {
		v.setY(0);
		tr_->setVelY(0);
	} else if (y + tr_->getH() >= game_->getWindowHeight()) {
		v.setY(game_->getWindowHeight() - tr_->getH());
		tr_->setVelY(0);
	}

	tr_->setPos(v);
}

