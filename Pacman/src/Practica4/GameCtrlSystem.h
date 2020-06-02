#ifndef __GAME_CTRL_SYSTEM_H__
#define __GAME_CTRL_SYSTEM_H__

#include "System.h"

struct GameState;

class GameCtrlSystem : public System 
{
private:
	GameState* gameState_;

public:
	GameCtrlSystem();

	void init() override;
	void update() override;

	// TODO: privatize this
	void onPacManDeath();
	void onNoMoreFood();

private:
	void startGame();
};

#endif // !__GAME_CTRL_SYSTEM_H__