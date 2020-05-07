#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "ECS.h"

class SDLGame;
class EntityManager;

class System 
{

protected:
	SDLGame* game_;
	EntityManager* entityManager_;

public:
	System() :
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

	virtual void init() 
	{
	}
	
	virtual void update() 
	{
	}
};

#endif // !__SYSTEM_H__