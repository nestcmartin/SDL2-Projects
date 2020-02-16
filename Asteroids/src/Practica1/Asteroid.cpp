#include "Asteroid.h"

Asteroid::Asteroid() :
	position_(Vector2D()),
	velocity_(Vector2D()),
	width_(0),
	height_(0),
	rotation_(0),
	generations_(0),
	isActive_(false)
{
}

Asteroid::Asteroid(Vector2D pos, Vector2D vel, double w, double h, double r, int g, bool active) :
	position_(pos),
	velocity_(vel),
	width_(w),
	height_(h),
	rotation_(r),
	generations_(g),
	isActive_(active)
{
}

Asteroid::~Asteroid()
{
}
