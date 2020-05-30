#ifndef __FIGHTER_SYSTEM_H__
#define __FIGHTER_SYSTEM_H__

#include <SDL.h>
#include <cstdint>

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class FightersSystem : public System {
public:
	FightersSystem();
	virtual ~FightersSystem();
	void init() override;
	void update() override;
	void resetFighterPositions();
	void receive(const messages::Message& msg) override;
private:
	void updateFighter(Entity* e);
	Entity* fighter0_;
	Entity* fighter1_;
};

#endif // !__FIGHTER_SYSTEM_H__