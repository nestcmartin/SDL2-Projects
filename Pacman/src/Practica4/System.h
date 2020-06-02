#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Messages.h"

#include "ECS.h"

class SDLGame;
class EntityManager;

class System
{
protected:
	ECS::SystemId id_;

	SDLGame* game_;
	EntityManager* enityManager_;

public:
	System(ECS::SystemId id) :
		id_(id),
		game_(nullptr),
		enityManager_(nullptr)
	{
	}

	virtual ~System()
	{
	}

	ECS::SystemId getId() { return id_; }
	void setGame(SDLGame* game) { game_ = game; }
	void setManager(EntityManager* mngr) { enityManager_ = mngr; }

	virtual void init() {};
	virtual void update() {};
	virtual void receive(const msg::Message& msg) {}
};

#endif // !__SYSTEM_H__