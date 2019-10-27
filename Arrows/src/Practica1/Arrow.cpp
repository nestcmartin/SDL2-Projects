#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s, int _a) :
	position_(_p),
	direction_(ARROW_DIR),
	speed_(_s),
	angle_(_a),
	width_(_w),
	height_(_h),
	texture_(_t)
{
	direction_.rotate(angle_);
}

Arrow::~Arrow()
{
}

SDL_Rect Arrow::getArrowhead() const
{
	Uint32 head = width_ / 4;
	
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX()) + (head * 3);
	rect.y = static_cast<int>(position_.getY());
	rect.w = head;
	rect.h = height_;

	return rect;
}

SDL_Rect Arrow::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}

bool Arrow::update()
{
	Vector2D vel = direction_ * speed_;
	position_ = position_ + vel;

	return position_.getX() < WIN_WIDTH &&
		position_.getY() < WIN_HEIGHT &&
		position_.getY() > 0;
}

void Arrow::render() const
{
	texture_->renderFrame(getRect(), 0, 0, angle_);
}

void Arrow::saveState(std::ofstream& stream)
{
	stream << position_ << " " << direction_ << " " << speed_ << " " << angle_ << std::endl;
}

void Arrow::loadState(std::ifstream& stream)
{
	stream >> position_ >> direction_ >> speed_ >> angle_;
}
