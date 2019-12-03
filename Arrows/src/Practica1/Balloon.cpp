#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(SDLApplication* _g, Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s) :
	position_(_p),
	direction_(BALLOON_DIR),
	width_(_w),
	height_(_h),
	spriteColumn_(0),
	texture_(_t),
	game_(_g),
	burst_(false),
	burstTime_(0)
{
	spriteRow_ = rand() % texture_->getNumRows();
	speed_ = BALLOON_MIN_SPEED + 
		static_cast<float>(rand()) / 
		(static_cast<float>(RAND_MAX / 
		(BALLOON_MAX_SPEED - BALLOON_MIN_SPEED)));
}

Balloon::~Balloon()
{
}

SDL_Rect Balloon::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}

bool Balloon::update()
{
	if (!burst_)
	{
		Vector2D vel = direction_ * speed_;
		position_ = position_ + vel;

		burst_ = game_->checkCollision(this);
		if (burst_)
		{
			burstTime_ = SDL_GetTicks();
			spriteColumn_++;
		}

		return position_.getY() > -static_cast<int>(height_);
	}
	else
	{
		Uint32 elapsedTime = SDL_GetTicks() - burstTime_;
		if (spriteColumn_ < ANIMATION_FRAMES && 
			(elapsedTime > FRAME_TIME * spriteColumn_)) 
			spriteColumn_++;
		
		return spriteColumn_ < ANIMATION_FRAMES;
	}
}

void Balloon::render() const
{
	texture_->renderFrame(getRect(), spriteRow_, spriteColumn_);
}

void Balloon::saveState(std::ofstream& stream)
{
	if (!burst_)
	{
		stream << position_ << " " << speed_ << " " << spriteRow_ << std::endl;
	}
}

void Balloon::loadState(std::ifstream& stream)
{
	stream >> position_ >> speed_ >> spriteRow_;
}
