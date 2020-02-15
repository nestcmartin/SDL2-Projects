#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include <vector>

#include "SDLGame.h"
#include "EntityManager.h"

class Asteroids 
{
private:
	const static int WINDOW_WIDTH = 1280;
	const static int WINDOW_HEIGHT = 720;

	bool exit_;

	SDLGame* game_;
	EntityManager* entityManager_;

public:
	Asteroids();
	virtual ~Asteroids();

	void run();
	void stop();

private:
	void initGame();
	void closeGame();

	void handleInput();
	void update();
	void render();
};

#endif // !__ASTEROIDS_H__