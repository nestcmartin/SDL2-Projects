#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include <vector>

#include "EntityManager.h"

#include "RenderSystem.h"
#include "GameCtrlSystem.h"
#include "CollisionSystem.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "FighterGunSystem.h"

#include "SDLGame.h"

class Asteroids
{
private:
	const static int WINDOW_WIDTH = 1080;
	const static int WINDOW_HEIGHT = 720;

	bool exit_;
	SDLGame* game_;
	EntityManager* entityManager_;

	RenderSystem* renderSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	CollisionSystem* collisionSystem_;
	FighterSystem* fighterSystem_;
	AsteroidsSystem* asteroidsSystem_;
	BulletsSystem* bulletSystem_;
	FighterGunSystem* fighterGunSystem_;

public:
	Asteroids();
	virtual ~Asteroids();

	void start();
	void stop();

private:
	void initGame();
	void closeGame();
};

#endif // !__ASTEROIDS_H__