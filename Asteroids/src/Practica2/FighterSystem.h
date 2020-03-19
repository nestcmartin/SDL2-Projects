#ifndef __FIGHTER_SYSTEM_H__
#define __FIGHTER_SYSTEM_H__

#include "Entity.h"
#include "EntityManager.h"

#include "Health.h"
#include "Transform.h"
#include "ImageComponent.h"

#include "System.h"

#include "SDLGame.h"
#include "InputHandler.h"

class FighterSystem : public System
{
private:
	Entity* fighter_;
	Transform* transform_;

public:
	FighterSystem() :
		fighter_(nullptr),
		transform_(nullptr)
	{
	}

	void onCollisionWithAsteroid(Entity* a)
	{
		transform_->position_ = Vector2D((game_->getWindowWidth() / 2) - 26, (game_->getWindowHeight() / 2) - 37);
		transform_->velocity_ = Vector2D(0, 0);
		transform_->rotation_ = 0;
	}

	void init() override
	{
		fighter_ = entityManager_->addEntity();
		transform_ = fighter_->addComponent<Transform>(Vector2D((game_->getWindowWidth() / 2) - 26, (game_->getWindowHeight() / 2) - 37), Vector2D(), 52, 75, 0);
		fighter_->addComponent<ImageComponent>(game_->getTextureManager()->getTexture(Resources::Airplanes));
		fighter_->addComponent<Health>(3, game_->getTextureManager()->getTexture(Resources::Heart));
		
		entityManager_->setHandler<_hdlr_Fighter>(fighter_);
	}

	void update() override
	{
		auto ih = InputHandler::instance();
		assert(transform_ != nullptr);
		if (ih->keyDownEvent())
		{
			if (InputHandler::instance()->isKeyDown(SDLK_LEFT))
			{
				transform_->rotation_ -= 5.0;
			}
			else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT))
			{
				transform_->rotation_ += 5.0;
			}
			else if (InputHandler::instance()->isKeyDown(SDLK_UP))
			{
				Vector2D newVel = transform_->velocity_ + Vector2D(0, -1).rotate(transform_->rotation_) * 0.5;
				if (newVel.magnitude() > 2.0) newVel = newVel.normalize() * 2.0;
				transform_->velocity_ = newVel;
			}
		}

		Vector2D newPos = transform_->position_ + transform_->velocity_ * 0.995;
		if (newPos.getX() < 0 || newPos.getX() >= game_->getWindowWidth() - transform_->width_ ||
			newPos.getY() < 0 || newPos.getY() >= game_->getWindowHeight() - transform_->height_)
			transform_->velocity_ = transform_->velocity_ * (-1);
		transform_->position_ = transform_->position_ + transform_->velocity_ * 0.995;
	}
};

#endif // !__FIGHTER_SYSTEM_H__