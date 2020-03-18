#ifndef __PACMAN_SYSTEM_H__
#define __PACMAN_SYSTEM_H__

#include "System.h"

#include "Entity.h"
#include "EntityManager.h"

#include "Transform.h"
#include "ImageComponent.h"

#include "SDLGame.h"
#include "InputHandler.h"

class PacManSystem : public System
{

private:
	Entity* pacman_;
	Transform* transform_;

public:
	PacManSystem() :
		pacman_(nullptr),
		transform_(nullptr)
	{
	}

	void init() override
	{
		pacman_ = entityManager_->addEntity();
		transform_ = pacman_->addComponent<Transform>(Vector2D(100.0, 100), Vector2D(), 50, 50, 0);
		pacman_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::PacMan));
		entityManager_->setHandler<_hdlr_PacMan>(pacman_);
	}

	void update() override
	{
		auto ih = InputHandler::instance();
		assert(transform_ != nullptr);
		if (ih->keyDownEvent())
		{
			if (ih->isKeyDown(SDLK_RIGHT))
			{
				transform_->rotation_ = transform_->rotation_ + 10;
				transform_->velocity_ = transform_->velocity_.rotate(10);
			}
			else if (ih->isKeyDown(SDLK_LEFT))
			{
				transform_->rotation_ = transform_->rotation_ - 10;
				transform_->velocity_ = transform_->velocity_.rotate(-10);
			}
			else if (ih->isKeyDown(SDLK_UP))
			{
				auto nv = Vector2D(0, -1).rotate(transform_->rotation_);
				transform_->velocity_ = nv * (transform_->velocity_.magnitude() + 0.5);
			}
			else if (ih->isKeyDown(SDLK_DOWN))
			{
				auto nv = Vector2D(0, -1).rotate(transform_->rotation_);
				transform_->velocity_ = nv * std::max(0.0, (transform_->velocity_.magnitude() - 0.5));
			}
		}

		transform_->position_ = transform_->position_ + transform_->velocity_;
		int x = transform_->position_.getX();
		int y = transform_->position_.getY();

		if (x <= 0 || x + transform_->width_ >= game_->getWindowWidth() ||
			y <= 0 || y + transform_->height_ >= game_->getWindowHeight())
		{
			transform_->rotation_ = fmod(transform_->rotation_ + 180.0, 360.0);
			transform_->velocity_ = transform_->velocity_.rotate(180);
		}
	}
};

#endif // !__PACMAN_SYSTEM_H__