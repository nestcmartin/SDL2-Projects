#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"

using CallBackOnClick = void(SDLApplication * app);

class MenuButton : public SDLGameObject, public EventHandler
{
private:
	enum ButtonState { 
		MOUSE_OUT, 
		MOUSE_OVER, 
		MOUSE_CLICKED 
	} currentState_;

	CallBackOnClick* callbackOnClick_;

public:
	MenuButton(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, CallBackOnClick* cb);
	virtual ~MenuButton();

	virtual bool handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;

};

#endif // !__MENU_BUTTON_H__

