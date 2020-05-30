#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Vector2D.h"
#include "Component.h"

struct Transform : Component {
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation) :
		Component(ECS::Transform), //
		position_(pos), //
		velocity_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation) //
	{
	}

	Transform() :
		Component(ECS::Transform), //
		position_(), //
		velocity_(), //
		width_(), //
		height_(), //
		rotation_() //
	{
	}

	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
};

#endif // !__TRANSFORM_H__