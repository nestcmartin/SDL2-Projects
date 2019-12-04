#include "GameState.h"
#include "SDLApplication.h"

GameState::GameState(SDLApplication* g) :
	app_(g)
{
}

GameState::~GameState()
{
	for (GameObject* o : gameObjects_)
	{
		delete o;
		o = nullptr;
	}

	eventHandlers_.clear();
	gameObjects_.clear();
}

void GameState::handleEvents(SDL_Event& event)
{
	bool handled = false;
	auto it = eventHandlers_.begin();
	while (!handled && it != eventHandlers_.end())
	{
		handled = (*it)->handleEvents(event);
		if (!handled) ++it;
	}
}

void GameState::update()
{
	for (GameObject* o : gameObjects_)
	{
		o->update();
	}
}

void GameState::render() const
{
	for (GameObject* o : gameObjects_)
	{
		o->render();
	}
}

void GameState::addEventHandler(EventHandler* e)
{
	auto it = eventHandlers_.insert(eventHandlers_.end(), e);
	e->setEventHandlerIterator(it);
}

void GameState::addGameObject(SDLGameObject* o)
{
	auto it = gameObjects_.insert(gameObjects_.end(), o);
	//o->setIteratorList(it);
}
