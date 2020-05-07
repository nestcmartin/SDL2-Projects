#ifndef __IMAGE_COMPONENT_H__
#define __IMAGE_COMPONENT_H__

#include "Component.h"

#include "Texture.h"

struct Image : Component 
{
	Image(Texture* tex) : 
		Component(ECS::Image),
		texture_(tex)
	{
	}
	
	Texture* texture_;
};

#endif // !__IMAGE_COMPONENT_H__