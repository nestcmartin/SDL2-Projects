#include "Bullet.h"

Bullet::Bullet() :
	position_(Vector2D()),
	velocity_(Vector2D()),
	width_(0),
	height_(0),
	rotation_(0),
	isActive_(false)
{
}

Bullet::Bullet(Vector2D pos, Vector2D vel, double w, double h, double r, bool active) :
	position_(pos),
	velocity_(vel),
	width_(w),
	height_(h),
	rotation_(r),
	isActive_(active)
{
}

Bullet::~Bullet()
{
}