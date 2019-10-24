#include "Bow.h"
#include "Game.h"

Bow::Bow(Game* g, Texture* t, Point2D p) :
	GameObject(g, t, p, BOW_DIR, BOW_WIDTH, BOW_HEIGHT, 0, BOW_SPEED),
	arrow_(nullptr), drawTime_(0), armed_(false)
{
}

Bow::~Bow()
{
}

void Bow::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT) charge();
		else if (event.key.keysym.sym == SDLK_RIGHT) loose();
		else if (event.key.keysym.sym == SDLK_UP) direction_ = Vector2D(0.0, -1.0);
		else if (event.key.keysym.sym == SDLK_DOWN) direction_ = Vector2D(0-0, 1.0);
		else if (event.key.keysym.sym == SDLK_a) angle_ -= BOW_ANGLE_INCREMENT;
		else if (event.key.keysym.sym == SDLK_d) angle_ += BOW_ANGLE_INCREMENT;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP ||
			event.key.keysym.sym == SDLK_DOWN)
		{
			direction_ = Vector2D(0.0, 0.0);
		}
	}
}

void Bow::update()
{
	// Limit rotation
	if (angle_ > BOW_ANGLE_LIMIT) angle_ = BOW_ANGLE_LIMIT;
	if (angle_ < -BOW_ANGLE_LIMIT) angle_ = -BOW_ANGLE_LIMIT;

	// Limit y-axis movement
	Vector2D p = position_ + (direction_ * speed_);
	if (p.getY() < 0.0 || p.getY() > (WIN_HEIGHT - BOW_HEIGHT)) return;
	
	GameObject::update();
}

void Bow::render() const
{
	GameObject::render();
	if (armed_)
	{
		game_->getTexture(Game::ARROW)->renderFrame({ static_cast<int>(position_.getX()), 
			static_cast<int>(position_.getY() + (height_ / 2) - (ARROW_HEIGHT / 2)),
			ARROW_WIDTH, ARROW_HEIGHT }, 0, 0, angle_);
	}
}

void Bow::saveState(std::ofstream& stream)
{
	GameObject::saveState(stream);
	if (armed_)	stream << 1 << " ";
	else stream << 0 << " ";
}

void Bow::loadState(std::ifstream& stream)
{
	GameObject::loadState(stream);
	stream >> armed_;
	if (armed_) charge();
}

void Bow::charge()
{
	if (!armed_ && game_->getArrowsLeft() > 0)
	{
		drawTime_ = SDL_GetTicks();
		armed_ = true;
	}
}

void Bow::loose()
{
	if (armed_)
	{
		double drawFactor = 1.0 + ((SDL_GetTicks() - drawTime_) / 10000.0);
		arrow_ = new Arrow(game_, game_->getTexture(Game::ARROW),
			{ position_.getX(), position_.getY() + (height_ / 2) - (ARROW_HEIGHT / 2) },
			angle_, ARROW_SPEED * drawFactor);
		game_->shootArrow(arrow_);
		armed_ = false;
	}
}
