#ifndef __STAR_WARS_H__
#define __STAR_WARS_H__

#include <vector>

#include "BulletsSystem.h"
#include "CollisionSystem.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"
#include "EntityManager.h"
#include "RenderSystem.h"
#include "SDLGame.h"
#include "NetworkingSystem.h"

class StarWars {

public:
	StarWars();
	StarWars(char* host, int port, char* name);
	virtual ~StarWars();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame(const char* name);
	void closeGame();

	char* host_;
	int port_;

	SDLGame* game_;
	EntityManager* manager_;
	bool exit_;

	RenderSystem* renderSystem_;
	FightersSystem* fightersSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	BulletsSystem* bulletsSystem_;
	CollisionSystem* collisionSystem_;
	NetworkingSystem* networkingSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};

#endif // !__STAR_WARS_H__