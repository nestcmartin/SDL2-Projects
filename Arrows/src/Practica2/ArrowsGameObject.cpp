#include "ArrowsGameObject.h"
#include "Game.h"

ArrowsGameObject::ArrowsGameObject(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	GameObject(),
	game_(g),
	texture_(t),
	width_(w),
	height_(h),
	position_(p),
	direction_(d),
	speed_(s),
	angle_(a)
{
}

ArrowsGameObject::~ArrowsGameObject()
{
}

void ArrowsGameObject::update()
{
	Vector2D velocity = direction_ * speed_;
	position_ = position_ + velocity;
}

void ArrowsGameObject::render() const
{
	SDL_Rect destRect = getDestRect();
	texture_->renderFrame(destRect, 0, 0, angle_);
}

void ArrowsGameObject::saveToFile(std::ofstream& stream)
{
	stream << position_ << " " << direction_ << " ";
	stream << speed_ << " " << angle_ << " ";
	stream << width_ << " " << height_ << " ";
}

void ArrowsGameObject::loadFromFile(std::ifstream& stream)
{
	stream >> position_ >> direction_;
	stream >> speed_ >> angle_;
	stream >> width_ >> height_;
}

SDL_Rect ArrowsGameObject::getDestRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}

SDL_Rect ArrowsGameObject::getCollisionRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}

void ArrowsGameObject::setIteratorList(const std::list<ArrowsGameObject*>::iterator& it)
{
	iterator_ = it;
}
