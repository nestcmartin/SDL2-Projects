#pragma once

#include "Component.h"

struct Score: Component {
	Score() :
			Component(ecs::Score), //
			leftScore_(0), //
			rightScore_(0) //
	{
	}

	int leftScore_;
	int rightScore_;
};
