#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Game* g, Texture* t, Point2D p) :
	GameObject(g, t, p, BALLOON_DIR, BALLOON_WIDTH, BALLOON_HEIGHT, 0, 0.0),
	burst_(false), burstTime_(0)
{
	spriteRow_ = rand() % sprite_->getNumRows();
	speed_ = BALLOON_MIN_SPEED + static_cast<float>(rand()) / 
		(static_cast<float>(RAND_MAX / (BALLOON_MAX_SPEED - BALLOON_MIN_SPEED)));
}

Balloon::~Balloon()
{
}

void Balloon::update()
{
	if (!burst_)
	{
		GameObject::update();
		burst_ = game_->checkCollision(this);
		if (burst_) 
		{ 
			burstTime_ = SDL_GetTicks(); 
			spriteCol_++; 
		}
		active_ = position_.getY() > -static_cast<int>(height_);
	}
	else
	{
		Uint32 elapsedTime = SDL_GetTicks() - burstTime_;
		if (spriteCol_ < BURST_ANIMATION_FRAMES &&
			(elapsedTime > BURST_FRAME_TIME* spriteCol_))
		{
			spriteCol_++;
		}
		active_ = spriteCol_ < BURST_ANIMATION_FRAMES;
	}
}
