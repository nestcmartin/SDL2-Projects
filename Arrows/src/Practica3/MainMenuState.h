#ifndef __MAIN_MENU_STATE_H__
#define __MAIN_MENU_STATE_H__

#include "GameState.h"
#include "MenuButton.h"

class SDLApplication;
class MainMenuState : public GameState
{
public:
	MainMenuState(SDLApplication* a);
	virtual ~MainMenuState();
	
	virtual std::string getStateName() const { return "MENU_STATE"; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;
};

#endif // !__MAIN_MENU_STATE_H__