#ifndef __ASTEROID_LIFE_TIME_H__
#define __ASTEROID_LIFE_TIME_H__

#include "Component.h"

struct AsteroidLifeTime : Component
{
	AsteroidLifeTime(int g) :
		numGenerations_(g)
	{
	}

	int numGenerations_;
};

#endif // !__ASTEROID_LIFE_TIME_H__