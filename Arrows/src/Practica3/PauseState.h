#ifndef __PAUSE_STATE_H__
#define __PAUSE_STATE_H__

#include "GameState.h"

class SDLApplication;
class PauseState : public GameState
{
public:
	PauseState(SDLApplication* a);
	virtual ~PauseState();

	virtual std::string getStateName() const { return "PAUSE_STATE"; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__PAUSE_STATE_H__
