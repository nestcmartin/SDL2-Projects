#pragma once
#include "Component.h"

struct Rotation: Component {
	Rotation() :
			rotation_(0) //
	{
	}
	double rotation_;
};

