#ifndef __LIFE_TIME_H__
#define __LIFE_TIME_H__

#include <SDL_stdinc.h>

#include "Component.h"

struct LifeTime : Component
{
	LifeTime() :
		creationTime_(0),
		lifeTime_(0)
	{
	}

	Uint32 creationTime_;
	Uint32 lifeTime_;
};

#endif // !__LIFE_TIME_H__