#pragma once

#include "Entity.h"
#include "ImageComponent.h"
#include "InputHandler.h"
#include "System.h"
#include "Transform.h"
#include "Manager.h"
#include "SDLGame.h"

class PacManSystem: public System {
public:
	PacManSystem() :
			pacman_(nullptr), //
			tr_(nullptr) {
	}

	void init() override {
		pacman_ = mngr_->addEntity();
		tr_ = pacman_->addComponent<Transform>(Vector2D(100.0, 100), Vector2D(),
				50, 50, 0);
		pacman_->addComponent<ImageComponent>(
				game_->getTextureMngr()->getTexture(Resources::PacMan));
		mngr_->setHandler<_hdlr_PacMan>(pacman_);
	}

	void update() override {
		auto ih = InputHandler::instance();
		assert(tr_ != nullptr);
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_RIGHT)) {
				tr_->rotation_ = tr_->rotation_ + 10;
				tr_->velocity_ = tr_->velocity_.rotate(10);
			} else if (ih->isKeyDown(SDLK_LEFT)) {
				tr_->rotation_ = tr_->rotation_ - 10;
				tr_->velocity_ = tr_->velocity_.rotate(-10);
			} else if (ih->isKeyDown(SDLK_UP)) {
				auto nv = Vector2D(0, -1).rotate(tr_->rotation_);
				tr_->velocity_ = nv * (tr_->velocity_.magnitude() + 0.5);
			} else if (ih->isKeyDown(SDLK_DOWN)) {
				auto nv = Vector2D(0, -1).rotate(tr_->rotation_);
				tr_->velocity_ = nv
						* std::max(0.0, (tr_->velocity_.magnitude() - 0.5));
			}
		}

		tr_->position_ = tr_->position_ + tr_->velocity_;
		int x = tr_->position_.getX();
		int y = tr_->position_.getY();

		if (x <= 0 || x + tr_->width_ >= game_->getWindowWidth() || y <= 0
				|| y + tr_->height_ >= game_->getWindowHeight()) {
			tr_->rotation_ = fmod(tr_->rotation_ + 180.0, 360.0);
			tr_->velocity_ = tr_->velocity_.rotate(180);
		}

	}
private:
	Entity *pacman_;
	Transform *tr_;
};

