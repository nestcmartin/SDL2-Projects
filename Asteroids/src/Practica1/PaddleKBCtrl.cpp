#include "PaddleKBCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

PaddleKBCtrl::PaddleKBCtrl() :
		PaddleKBCtrl(SDLK_UP, SDLK_DOWN, SDLK_SPACE) {
}

PaddleKBCtrl::PaddleKBCtrl(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop) :
		Component(ecs::PaddleKBCtrl), //
		up_(up), //
		down_(down), //
		stop_(stop),
		tr_(nullptr)//
{
}

PaddleKBCtrl::~PaddleKBCtrl() {
}

void PaddleKBCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void PaddleKBCtrl::update() {

	InputHandler *ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(up_)) {
			tr_->setVelY(tr_->getVel().getY() - 2);
		} else if (ih->isKeyDown(down_)) {
			tr_->setVelY(tr_->getVel().getY() + 2);
		} else if (ih->isKeyDown(stop_)) {
			tr_->setVelY(0);
		}

	}
}

