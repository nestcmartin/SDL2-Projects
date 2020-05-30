#ifndef __SYSTEM_H__
#define __SYSTEM_H__

class SDLGame;
class EntityManager;

#include "ECS.h"
#include "messages.h"

class System {
public:
	System(ECS::SysIdType id) :
		id_(id), manager_(nullptr), game_(nullptr) {
	}

	virtual ~System() {
	}

	ECS::SysIdType getId() {
		return id_;
	}

	void setGame(SDLGame* game) {
		game_ = game;
	}

	void setMngr(EntityManager* mngr) {
		manager_ = mngr;
	}

	virtual void init() {};
	virtual void update() {};
	virtual void receive(const messages::Message& msg) {}

protected:
	ECS::SysIdType id_;
	EntityManager* manager_;
	SDLGame* game_;

};

#endif // !__SYSTEM_H__