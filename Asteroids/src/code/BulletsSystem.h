#pragma once

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class BulletsSystem: public System {
public:
	BulletsSystem();
	void update() override;
	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();
private:
};


