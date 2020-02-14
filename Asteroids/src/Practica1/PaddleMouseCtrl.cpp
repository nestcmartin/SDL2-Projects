#include "PaddleMouseCtrl.h"

#include "InputHandler.h"
#include "Entity.h"

PaddleMouseCtrl::PaddleMouseCtrl() :
		Component(ecs::PaddleMouseCtrl), //
		tr_(nullptr) //
{
}

PaddleMouseCtrl::~PaddleMouseCtrl() {
}

void PaddleMouseCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void PaddleMouseCtrl::update() {
	InputHandler *ih = InputHandler::instance();

	if (ih->mouseMotionEvent()) {
		tr_->setPosY(ih->getMousePos().getY());
	}

}

