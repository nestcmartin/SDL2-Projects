#include "EntityManager.h"

#include "GameState.h"
#include "AnimatedImage.h"

#include "PacManSystem.h"

#include "InputHandler.h"

#include "SDLGame.h"


PacManSystem::PacManSystem() :
	System(ECS::_sys_PacMan),
	pacman_(nullptr), 
	transform_(nullptr)
{
}

void PacManSystem::init() 
{
	pacman_ = enityManager_->addEntity();

	transform_ = pacman_->addComponent<Transform>();
	resetPacManPosition();

	auto animatedImage = pacman_->addComponent<AnimatedImage>();
	animatedImage->setSpriteTime(100);
	
	Texture* spritesTex = game_->getTextureMngr()->getTexture(Resources::PacManSprites);
	for (int i = 0; i < 4; i++) 
	{
		animatedImage->addSprite(spritesTex, { i * 128, 0, 128, 128 });
	}

	enityManager_->setHandler(ECS::_hdlr_PacManEntity, pacman_);
}

void PacManSystem::update() 
{
	auto gameState = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);
	if (gameState->state_ != GameState::RUNNING) return;

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

	// Move, but stop on borders
	Vector2D oldPosition = transform_->position_;

	transform_->position_ = transform_->position_ + transform_->velocity_;
	int x = transform_->position_.getX();
	int y = transform_->position_.getY();

	if (x <= 0 || x + transform_->width_ >= game_->getWindowWidth() ||
		y <= 0 || y + transform_->height_ >= game_->getWindowHeight()) 
	{
		transform_->position_ = oldPosition;
		transform_->velocity_ = Vector2D(0.0, 0.0);
	}
}

void PacManSystem::resetPacManPosition() 
{
	transform_->position_ = Vector2D((game_->getWindowWidth() - transform_->width_) / 2, (game_->getWindowHeight() - transform_->height_) / 2);
	transform_->velocity_ = Vector2D(0.0, 0.0);
	transform_->width_ = transform_->height_ = 30.0;
	transform_->rotation_ = 0.0;
}
