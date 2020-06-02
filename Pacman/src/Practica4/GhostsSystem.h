#ifndef __GHOSTS_SYSTEM_H__
#define __GHOSTS_SYSTEM_H__

#include <SDL.h>

#include "System.h"

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
	void receive(const msg::Message& msg) override;

private:
	void onCollisionWithPacMan(Entity *e);
	void addGhosts(std::size_t n);
	void disableAll();
};

#endif // !__GHOSTS_SYSTEM_H__