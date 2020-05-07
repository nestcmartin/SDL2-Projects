#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "ECS.h"

#include "Messages.h"

class SDLGame;
class EntityManager;

class System 
{

protected:
	SDLGame* game_;
	EntityManager* entityManager_;

	ECS::SysIdType id_;

public:
	System(ECS::SysIdType id) :
		id_(id),
		game_(nullptr) ,
		entityManager_(nullptr)
	{
	}

	virtual ~System() 
	{
	}

	void setGame(SDLGame* game) 
	{
		game_ = game;
	}

	void setMngr(EntityManager* mngr) 
	{
		entityManager_ = mngr;
	}

	ECS::SysIdType getId() {
		return id_;
	}

	virtual void init() {}
	virtual void update() {}
	virtual void receive(const MSG::Message& msg) {}
};

#endif // !__SYSTEM_H__