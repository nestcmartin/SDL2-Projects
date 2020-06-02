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
	void receive(const msg::Message& msg) override;

private:
	void startGame();
	void onPacManDeath();
	void onNoMoreFood();
};

#endif // !__GAME_CTRL_SYSTEM_H__