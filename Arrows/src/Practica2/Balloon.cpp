#include "Balloon.h"
#include "Game.h"

int Balloon::count = 0;

Balloon::Balloon(SDLApplication* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	burst_(false),
	burstTime_(SDL_GetTicks()),
	spriteRow_(0),
	spriteColumn_(0)
{
	spriteRow_ = rand() % texture_->getNumRows();
	speed_ = BALLOON_MIN_SPEED + 
		static_cast<float>(rand()) / 
		(static_cast<float>(RAND_MAX / 
		(BALLOON_MAX_SPEED - BALLOON_MIN_SPEED)));
	count++;
}

Balloon::~Balloon()
{
}

void Balloon::update()
{
	if (!burst_)
	{
		ArrowsGameObject::update();
		checkBurst();

		if (position_.getY() < -static_cast<int>(height_))
		{
			count--;
			game_->killBalloon(iterator_);
		}
	}
	else
	{
		animate();

		if (spriteColumn_ < BURST_ANIMATION_FRAMES)
		{
			count--;
			game_->killBalloon(iterator_);
		}
	}
}

void Balloon::render() const
{
	texture_->renderFrame(getDestRect(), spriteRow_, spriteColumn_, angle_);
}

void Balloon::saveToFile(std::ofstream& stream)
{
	ArrowsGameObject::saveToFile(stream);
	stream << spriteRow_ << " " << spriteColumn_ << " " << burst_ << " ";
}

void Balloon::loadFromFile(std::ifstream& stream)
{
	ArrowsGameObject::loadFromFile(stream);
	stream >> spriteRow_ >> spriteColumn_ >> burst_;
}

void Balloon::checkBurst()
{
	burst_ = game_->hitBalloon(this);
	if (burst_)
	{
		burstTime_ = SDL_GetTicks();
		spriteColumn_++;
	}
}

void Balloon::animate()
{
	Uint32 elapsedTime = SDL_GetTicks() - burstTime_;
	if (spriteColumn_ < BURST_ANIMATION_FRAMES &&
		(elapsedTime > BURST_FRAME_TIME * spriteColumn_))
		spriteColumn_++;
}
