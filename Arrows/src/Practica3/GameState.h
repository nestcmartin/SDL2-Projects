#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <list>

#include "Font.h"
#include "Constants.h"
#include "EventHandler.h"
#include "SDLGameObject.h"

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

	virtual std::string getStateName() const = 0;

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;

	inline SDLApplication* getApp() const { return app_; }

protected:
	void addEventHandler(EventHandler* e);
	void addGameObject(SDLGameObject* o);
};

#endif // !__GAME_STATE_H__

