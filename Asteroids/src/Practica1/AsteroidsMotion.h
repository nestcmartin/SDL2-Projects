#ifndef __ASTEROIDS_MOTION_H__
#define __ASTEROIDS_MOTION_H__

#include "Component.h"
#include "AsteroidsPool.h"

class AsteroidsMotion : public Component
{
private:
	const double ROTATION_FACTOR = 0.5;

	AsteroidsPool* asteroidsPool_;

public:
	AsteroidsMotion();
	virtual ~AsteroidsMotion();

	void init() override;
	void update() override;
};

#endif // !__ASTEROIDS_MOTION_H__
