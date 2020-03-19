#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "Component.h"
#include "Texture.h"

struct Health : Component
{
	Health(int lives, Texture* texture) :
		numLives_(lives),
		texture_(texture)
	{
	}

	int numLives_;
	Texture* texture_;
};

#endif // !__HEALTH_H__
