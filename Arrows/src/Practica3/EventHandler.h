#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <list>

#include "SDL.h"

class EventHandler
{
protected:
	std::list<EventHandler*>::iterator eventHandlerIt_;

public:
	virtual bool handleEvents(SDL_Event& event) = 0;

	void setEventHandlerIterator(std::list<EventHandler*>::iterator it) { eventHandlerIt_ = it; }
};

#endif // !__EVENT_HANDLER_H__
