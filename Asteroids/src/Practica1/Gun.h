#ifndef __GUN_H__
#define __GUN_H__

#include "Component.h"
#include "Transform.h"
#include "BulletsPool.h"

class Gun : public Component
{
private:
	const double BULLET_SPEED = 2.0;
	const Uint32 COOLDOWN_TIME = 250;

	Transform* transform_;
	BulletsPool* bulletsPool_;

	SDL_Keycode fireKey_;
	Uint32 lastShootTime_;

public:
	Gun();
	Gun(SDL_Keycode fire, BulletsPool* pool);
	virtual ~Gun();

	void init() override;
	void update() override;
};

#endif // !__GUN_H__

