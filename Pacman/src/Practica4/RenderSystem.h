#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "GameState.h"

#include "System.h"


class RenderSystem : public System
{
public:
	RenderSystem();

	void update() override;

private:
	void drawAnimatedEntity(Entity* e);
	void drawFood(GameState* gs);
	void drawGhosts(GameState* gs);
	void drawPacMan(GameState* gs);
	void drawState(GameState* gs);
};

#endif // !__RENDER_SYSTEM_H__