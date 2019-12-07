#ifndef __END_STATE_H__
#define __END_STATE_H__

#include "GameState.h"

#include "LeaderBoard.h"

class SDLApplication;
class EndState : public GameState
{
private:
	bool win_;
	int finalScore_;
	LeaderBoard* leaderBoard_;

public:
	EndState(SDLApplication* a, int score, bool win);
	virtual ~EndState();

	virtual std::string getStateName() const { return "END_STATE"; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__END_STATE_H__
