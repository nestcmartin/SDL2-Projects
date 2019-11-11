#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "SDL.h"

class EventHandler
{
public:
	virtual void handleEvents(SDL_Event& event) = 0;
};

#endif // !__EVENT_HANDLER_H__
