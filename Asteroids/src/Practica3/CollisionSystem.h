#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include "System.h"

class CollisionSystem : public System 
{
public:
	CollisionSystem();
	virtual ~CollisionSystem();

	void update() override;
};

#endif // !__COLLISION_SYSTEM_H__