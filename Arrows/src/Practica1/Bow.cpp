#include "Bow.h"
#include "Game.h"

Bow::Bow(Game* _g, Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s) :
	position_(_p),
	direction_({ 0, 0 }),
	speed_(_s),
	angle_(0),
	width_(_w),
	height_(_h),
	drawTime_(0),
	texture_(_t),
	arrow_(nullptr),
	game_(_g),
	armed_(false)
{
}

Bow::~Bow()
{
}

void Bow::charge()
{
	if (!armed_ && game_->hasArrows())
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
		arrow_ = new Arrow(game_->getTexture(Game::ARROW), 
					  { position_.getX(), position_.getY() + (height_ / 2) },
					  ARROW_WIDTH, ARROW_HEIGHT, ARROW_SPEED * drawFactor, angle_);
		game_->shootArrow(arrow_);
		armed_ = false;
	}
}

SDL_Rect Bow::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}

void Bow::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT) charge();
		else if (event.key.keysym.sym == SDLK_RIGHT) loose();
		else if (event.key.keysym.sym == SDLK_UP) direction_ = Vector2D(0, -1);
		else if (event.key.keysym.sym == SDLK_DOWN) direction_ = Vector2D(0, 1);
		else if (event.key.keysym.sym == SDLK_a) angle_ -= 3;
		else if (event.key.keysym.sym == SDLK_d) angle_ += 3;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP ||
			event.key.keysym.sym == SDLK_DOWN)
		{
			direction_ = Vector2D(0, 0);
		}
	}
}

void Bow::update()
{
	Vector2D vel = direction_ * speed_;
	
	// Limit y-axis movement
	if ((position_ + vel).getY() < 0.0 ||
		(position_ + vel).getY() > (WIN_HEIGHT - BOW_HEIGHT)) return;

	// Limit rotation
	if (angle_ > 60) angle_ = 60;
	if (angle_ < -60) angle_ = -60;
	
	position_ = position_ + vel;
}

void Bow::render() const
{
	texture_->renderFrame(getRect(), 0, 0, angle_);
	if (armed_)
	{
		game_->getTexture(Game::ARROW)->renderFrame({ static_cast<int>(position_.getX()), 
												  static_cast<int>(position_.getY() + (height_ / 2)), 
												  ARROW_WIDTH, ARROW_HEIGHT }, 0, 0, angle_);
	}
}

void Bow::saveState(std::ofstream& stream)
{
	stream << position_ << " " << angle_ << std::endl;
}

void Bow::loadState(std::ifstream& stream)
{
	stream >> position_ >> angle_;
}
