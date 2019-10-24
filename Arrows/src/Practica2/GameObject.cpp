#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game* g, Texture* t, Point2D p, Vector2D d, Uint32 w, Uint32 h, int a, double s) :
	game_(g),
	sprite_(t),
	position_(p),
	direction_(d),
	width_(w),
	height_(h),
	angle_(a),
	speed_(s),
	active_(true),
	spriteRow_(0),
	spriteCol_(0)
{
}

GameObject::~GameObject()
{
}

SDL_Rect GameObject::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_; rect.h = height_;
	return rect;
}

void GameObject::handleEvents(SDL_Event& e)
{
}

void GameObject::update()
{
	Vector2D velocity = speed_ * direction_;
	position_ = position_ + velocity;
}

void GameObject::render() const
{
	SDL_Rect destRect = getRect();
	sprite_->renderFrame(destRect, spriteRow_, spriteCol_, angle_);
}

void GameObject::saveState(std::ostream& out)
{
	out << position_ << " " << direction_ << " ";
	out << width_ << " " << height_ << " ";
	out << angle_ << " " << speed_ << " ";
	out << spriteRow_ << " " << spriteCol_ << " ";
}

void GameObject::loadState(std::istream& in)
{
	in >> position_ >> direction_;
	in >> width_ >> height_;
	in >> angle_ >> speed_;
	in >> spriteRow_ >> spriteCol_;
}
