#ifndef __IMAGE_COMPONENT_H__
#define __IMAGE_COMPONENT_H__

#include "Component.h"
#include "Texture.h"

struct ImageComponent : Component 
{
	ImageComponent(Texture* tex) : 
		texture_(tex)
	{
	}
	
	Texture* texture_;
};

#endif // !__IMAGE_COMPONENT_H__