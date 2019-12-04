#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__

#include "GameState.h"

class SDLApplication;
class PlayState : public GameState
{
public:
	PlayState(SDLApplication* a);
	virtual ~PlayState();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__PLAY_STATE_H__
