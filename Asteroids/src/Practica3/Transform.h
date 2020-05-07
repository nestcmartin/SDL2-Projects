#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Component.h"

#include "Vector2D.h"

struct Transform : Component
{
	Transform() :
		position_(),
		velocity_(),
		width_(),
		height_(),
		rotation_()
	{
	}

	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation) :
		position_(pos),
		velocity_(vel),
		width_(width),
		height_(height),
		rotation_(0.0)
	{
	}

	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
};

#endif // !__TRANSFORM_H__