#pragma once

#include <vector>

#include "GameCtrlSystem.h"
#include "Manager.h"
#include "NetworkingSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "SDLGame.h"

class PingPong {

public:
	PingPong(char *host, int port);
	virtual ~PingPong();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	char *host_;
	int port_;

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;

	NetworkingSystem *networkingSystem_;
	RenderSystem *renderSystem_;
	PhysicsSystem *physicsSystem_;
	GameCtrlSystem *gameCtrlSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
