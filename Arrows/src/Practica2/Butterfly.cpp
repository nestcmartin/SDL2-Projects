#include "Butterfly.h"
#include "Game.h"

int Butterfly::count = 0;

Butterfly::Butterfly(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	spriteRow_(0),
	spriteColumn_(0),
	dead_(false)
{
	randomDirection();
	randomPosition();
	lastTime_ = SDL_GetTicks();
	count++;
}

Butterfly::~Butterfly()
{
}

void Butterfly::update()
{	
	if (!dead_)
	{
		checkDead();
		randomMovement();
		animate();
	}

	ArrowsGameObject::update();

	if (position_.getY() > WIN_HEIGHT) game_->killButterfly(iterator_);
}

void Butterfly::render() const
{
	SDL_Rect destRect = getDestRect();
	texture_->renderFrame(destRect, spriteRow_, spriteColumn_, angle_);
}

void Butterfly::saveToFile(std::ofstream& stream)
{
	ArrowsGameObject::saveToFile(stream);
	stream << spriteRow_ << " " << spriteColumn_ << " ";
}

void Butterfly::loadFromFile(std::ifstream& stream)
{
	ArrowsGameObject::loadFromFile(stream);
	stream >> spriteRow_ >> spriteColumn_;
}

void Butterfly::animate()
{
	if (direction_.getX() == 1) spriteRow_ = 1;
	else spriteRow_ = 0;
	spriteColumn_ = int((SDL_GetTicks() / BUTTERFLY_FRAME_TIME) % BUTTERFLY_ANIMATION_FRAMES);
}

void Butterfly::checkDead()
{
	dead_ = game_->hitButterfly(this);
	if (dead_)
	{
		spriteColumn_ = 0;
		direction_.set(0, 1);
	}
}

void Butterfly::randomMovement()
{
	Uint32 elapsedTime = SDL_GetTicks() - lastTime_;
	if (elapsedTime > BUTTERFLY_TIMER)
	{
		randomDirection();
		lastTime_ = SDL_GetTicks();
	}

	if (position_.getX() + direction_.getX() * speed_ < 150)
	{
		lastTime_ = SDL_GetTicks();
		direction_.setX(1);
	}
	else if (position_.getX() + direction_.getX() * speed_ > WIN_WIDTH)
	{
		lastTime_ = SDL_GetTicks();
		direction_.setX(-1);
	}
	else if (position_.getY() + direction_.getY() * speed_ < 0)
	{
		lastTime_ = SDL_GetTicks();
		direction_.setY(1);
	}
	else if (position_.getY() + direction_.getY() * speed_ > WIN_HEIGHT)
	{
		lastTime_ = SDL_GetTicks();
		direction_.setY(-1);
	}
}

void Butterfly::randomPosition()
{
	int x = rand() % SPAWN_SPACE + SPAWN_LOWER_BOUND;
	int y = rand() % WIN_HEIGHT + 100;
	position_.setX(x);
	position_.setY(y);
}

void Butterfly::randomDirection()
{
	int sx = rand() % 2;
	int sy = rand() % 2;
	sx == 0 ? direction_.setX(1) : direction_.setX(-1);
	sy == 0 ? direction_.setY(1) : direction_.setY(-1);
}
