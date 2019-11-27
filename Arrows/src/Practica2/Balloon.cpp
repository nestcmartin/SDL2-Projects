#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	burst_(false),
	burstTime_(0),
	spriteRow_(0),
	spriteColumn_(0)
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

void Balloon::update()
{
	if (!burst_)
	{
		ArrowsGameObject::update();
		checkBurst();
	}
	else
	{
		animate();
	}
}

void Balloon::render() const
{
	texture_->renderFrame(getDestRect(), spriteRow_, spriteColumn_, angle_);
}

void Balloon::saveToFile(std::ofstream& stream)
{
	ArrowsGameObject::saveToFile(stream);
	stream << spriteRow_ << " ";
}

void Balloon::loadFromFile(std::ifstream& stream)
{
	ArrowsGameObject::loadFromFile(stream);
	stream >> spriteRow_;
}

void Balloon::checkBurst()
{
	burst_ = game_->checkCollision(this);
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
