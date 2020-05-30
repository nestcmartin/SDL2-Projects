#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem: public System {
public:
	GameCtrlSystem();
    void recieve(const msg::Message& msg) override;
	void init() override;
	void update() override;
private:
	void onBallExit(uint8_t side);
	void startRound();
};

