#ifndef __FIGHTER_CTRL_H__
#define __FIGHTER_CTRL_H__

#include "Component.h"
#include "Transform.h"

class FighterCtrl : public Component
{
private:
	const double ROTATION_DEGREES = 5.0;
	const double SPEED_LIMIT = 2.0;
	const double THRUST = 0.5;

	SDL_Keycode thrustKey_;
	SDL_Keycode turnLeftKey_;
	SDL_Keycode turnRightKey_;

	Transform* transform_;

public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode up, SDL_Keycode right, SDL_Keycode left);
	virtual ~FighterCtrl();

	void init() override;
	void update() override;
};

#endif // !__FIGHTER_CTRL_H__
