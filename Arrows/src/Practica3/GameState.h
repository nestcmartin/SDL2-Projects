#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <list>

#include "Constants.h"
#include "EventHandler.h"
#include "ArrowsGameObject.h"

class SDLApplication;
class GameState
{
protected:
	SDLApplication* app_;

	std::list<GameObject*> gameObjects_;
	std::list<EventHandler*> eventHandlers_;

public:
	GameState(SDLApplication* g);
	virtual ~GameState();

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;

protected:
	void addEventHandler(EventHandler* e);
	void addGameObject(ArrowsGameObject* o);
};

#endif // !__GAME_STATE_H__
