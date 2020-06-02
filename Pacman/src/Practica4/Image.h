#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Component.h"

#include "Texture.h"

struct Image : Component
{
	Image(Texture* tex) :
		Component(ECS::ImageComponent),
		texture_(tex)
	{
	}

	Texture* texture_;
};

#endif // !__IMAGE_H__