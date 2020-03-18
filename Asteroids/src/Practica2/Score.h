#ifndef __SCORE_H__
#define __SCORE_H__

#include "Component.h"

struct Score : Component
{
	Score() :
		points_(0)
	{
	}

	unsigned int points_;
};

#endif // !__SCORE_H__