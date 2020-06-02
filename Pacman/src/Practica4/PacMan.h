#ifndef __PACMAN_H__
#define __PACMAN_H__

#include <vector>

#include "EntityManager.h"

#include "FoodSystem.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "RenderSystem.h"
#include "AudioSystem.h"

#include "SDLGame.h"

class PacMan 
{
	const static int WINDOW_WIDTH = 640;
	const static int WINDOW_HEIGHT = 480;

private:
	bool exit_;

	SDLGame* game_;
	EntityManager* entityManager_;

	FoodSystem* foodSystem_;
	GhostsSystem* ghostsSystem_;
	PacManSystem* pacmanSystem_;
	CollisionSystem* collisionSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	RenderSystem* renderSystem_;
	AudioSystem* audioSystem_;

public:
	PacMan();
	virtual ~PacMan();

	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void initFactories();
};

#endif // !__PACMAN_H__