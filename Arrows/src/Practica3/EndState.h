#ifndef __END_STATE_H__
#define __END_STATE_H__

#include "GameState.h"

class SDLApplication;
class EndState : public GameState
{
public:
	EndState(SDLApplication* a);
	virtual ~EndState();

	virtual std::string getStateName() const { return "END_STATE"; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__END_STATE_H__
