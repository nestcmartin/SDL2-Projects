#ifndef __GAME_CTRL_SYSTEM_H__
#define __GAME_CTRL_SYSTEM_H__

#include "System.h"

#include "ECS.h"
#include "Score.h"
#include "StarsSystem.h"

class GameCtrlSystem : public System 
{
public:
	void init() override 
	{
		Entity* e = entityManager_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;
		entityManager_->setHandler<_hdlr_GameState>(e);
	}

	void update() override 
	{
		auto ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) 
		{
			entityManager_->getSystem<StarsSystem>()->addStars(10);
		}
	}

};

#endif // !__GAME_CTRL_SYSTEM_H__