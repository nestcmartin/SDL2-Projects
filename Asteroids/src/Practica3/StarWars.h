#ifndef __STAR_WARS_H__
#define __STAR_WARS_H__

#include <vector>

#include "EntityManager.h"

#include "RenderSystem.h"
#include "BulletsSystem.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"
#include "CollisionSystem.h"

#include "SDLGame.h"

class StarWars
{
private:
	const static int WINDOW_WIDTH = 1080;
	const static int WINDOW_HEIGHT = 720;

	bool exit_;
	SDLGame* game_;
	EntityManager* entityManager_;

	RenderSystem* renderSystem_;
	BulletsSystem* bulletSystem_;
	FightersSystem* fighterSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	CollisionSystem* collisionSystem_;

public:
	StarWars();
	virtual ~StarWars();

	void start();
	void stop();

private:
	void initGame();
	void closeGame();
};

#endif // !__STAR_WARS_H__