#ifndef __GAME_CTRL_SYSTEM_H__
#define __GAME_CTRL_SYSTEM_H__

#include "ECS.h"
#include "System.h"
#include "SDLGame.h"
#include "EntityManager.h"

class GameCtrlSystem : public System {
public:
	enum State : uint8_t {
		WAITING, READY, RUNNING, ROUNDOVER, GAMEOVER
	};

	GameCtrlSystem();
	void init() override;
	void update() override;
	State getState() {
		return state_;
	}
	void onFighterDeath(uint8_t fighterId);
	uint8_t getScore(uint8_t fighterId) {
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}

	void receive(const messages::Message& msg) override;

private:
	void resetScore();
	void startGame();
	void sendMyInfo();

	uint8_t score[2];
	State state_;
};

#endif // !__GAME_CTRL_SYSTEM_H__