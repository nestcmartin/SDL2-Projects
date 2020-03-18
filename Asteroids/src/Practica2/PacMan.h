#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include <vector>

#include "EntityManager.h"

#include "RenderSystem.h"
#include "GameCtrlSystem.h"
#include "CollisionSystem.h"
#include "PacManSystem.h"
#include "StarsSystem.h"

#include "SDLGame.h"

class PacMan {

public:
	PacMan();
	virtual ~PacMan();

	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	void addStars(std::size_t n);

	SDLGame* game_;
	EntityManager* entityManager_;
	bool exit_;

	RenderSystem* renderSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	CollisionSystem* collisionSystem_;
	PacManSystem* pacmanSystem_;
	StarsSystem* starsSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};

#endif // !__ASTEROIDS_H__