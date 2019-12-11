#include "ArrowsGameObject.h"
#include "GameState.h"

ArrowsGameObject::ArrowsGameObject(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	SDLGameObject(g, t, w, h, p),
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

	if (position_.getX() < 0 || position_.getX() > WIN_WIDTH || 
		position_.getY() < -static_cast<int>(height_) || position_.getY() > WIN_HEIGHT)
		throw FileFormatError("Position out of bounds.\n");
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

void ArrowsGameObject::setIteratorList(const std::list<GameObject*>::iterator& it)
{
	iterator_ = it;
}