#ifndef __GHOSTS_SYSTEM_H__
#define __GHOSTS_SYSTEM_H__


#include "System.h"
#include <SDL.h>

class GhostsSystem : public System 
{
private:
	int maxGhosts_;
	int numOfGhosts_;
	Uint32 lastTimeAdded_;

public:
	GhostsSystem();
	
	void init() override;
	void update() override;

	// TODO: privatize this
	void onCollisionWithPacMan(Entity *e);
	void addGhosts(std::size_t n);
	void disableAll();
};

#endif // !__GHOSTS_SYSTEM_H__