#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "ECS.h"

struct Component
{
	Component(ECS::ComponentId id) :
		id_(id) 
	{
	}

	ECS::ComponentId id_;
};

#endif // !__COMPONENT_H__