#ifndef __BULLETS_MOTION_H__
#define __BULLETS_MOTION_H__

#include "Component.h"
#include "BulletsPool.h"

class BulletsMotion : public Component
{
private:
	BulletsPool* bulletsPool_;

public:
	BulletsMotion();
	virtual ~BulletsMotion();

	void init() override;
	void update() override;
};

#endif // !__BULLETS_MOTION_H__