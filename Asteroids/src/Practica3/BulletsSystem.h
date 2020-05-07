#ifndef __BULLETS_SYSTEM_H__
#define __BULLETS_SYSTEM_H__

#include "Entity.h"

#include "System.h"

#include "Vector2D.h"

class BulletsSystem : public System
{
public:
	BulletsSystem();

	void update() override;
	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();

};

#endif // !__BULLETS_SYSTEM_H__
