#pragma once

#include "Component.h"

struct Score: Component {
	Score() :
			points_(0) //
	{
	}

	unsigned int points_;
};

