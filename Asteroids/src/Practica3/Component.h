#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "ECS.h"

struct Component 
{
	Component(ECS::CmpIdType id) :
		id_(id) 
	{
	}

	ECS::CmpIdType id_;
};

#endif // !__COMPONENT_H__