#ifndef __FIGHTERS_SYSTEM_H__
#define __FIGHTERS_SYSTEM_H__

#include "Entity.h"

#include "System.h"

#include "Vector2D.h"

class FightersSystem : public System
{
private:
	Entity* fighter0_;
	Entity* fighter1_;

public:
	FightersSystem();
	virtual ~FightersSystem();

	void init() override;
	void update() override;
	void resetFighterPositions();

private:
	void updateFighter(Entity* e);
};

#endif // !__FIGHTERS_SYSTEM_H__