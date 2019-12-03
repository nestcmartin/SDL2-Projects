#ifndef __MAIN_MENU_STATE_H__
#define __MAIN_MENU_STATE_H__

#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState(SDLApplication* g);
	virtual ~MainMenuState();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__MAIN_MENU_STATE_H__