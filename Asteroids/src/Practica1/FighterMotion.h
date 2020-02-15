#ifndef __FIGHTER_MOTION_H__
#define __FIGHTER_MOTION_H__

#include "Component.h"
#include "Transform.h"

class FighterMotion : public Component
{
private:
	const double STOP_FACTOR = 0.995;

	Transform* transform_;

public:
	FighterMotion();
	virtual ~FighterMotion();

	void init() override;
	void update() override;
};
#endif // !__FIGHTER_MOTION_H__

