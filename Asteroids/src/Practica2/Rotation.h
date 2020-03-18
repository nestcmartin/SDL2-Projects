#ifndef __ROTATION_H__
#define __ROTATION_H__

#include "Component.h"

struct Rotation : Component 
{
	Rotation() :
		rotation_(0)
	{
	}

	double rotation_;
};

#endif // !__ROTATION_H__