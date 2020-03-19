#ifndef __GAME_CTRL_SYSTEM_H__
#define __GAME_CTRL_SYSTEM_H__

#include "Score.h"
#include "Health.h"
#include "GameState.h"

#include "System.h"
#include "AsteroidsSystem.h"

#include "ECS.h"

class GameCtrlSystem : public System
{
private:
	Score* score_;
	GameState* state_;

public:
	void onFighterDeath()
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Asteroid>()) e->setActive(false);
		for (auto& e : entityManager_->getGroupEntities<_grp_Bullet>()) e->setActive(false);
		
		Health* health = entityManager_->getHandler<_hdlr_Fighter>()->getComponent<Health>();

		if (--health->numLives_ <= 0)
		{
			state_->running_ = false;
			state_->gameOver_ = true;
			state_->win_ = false;
			onGameOver();
		}
		else
		{
			state_->running_ = false;
			state_->gameOver_ = false;
			state_->win_ = false;
		}
	}

	void onAsteroidsExtinction()
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Bullet>()) e->setActive(false);
		state_->running_ = false;
		state_->gameOver_ = true;
		state_->win_ = true;
		onGameOver();
	}

	void onGameOver()
	{
		entityManager_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->numLives_ = 3;
		if (!state_->win_) score_ = 0;

	}

	void init() override
	{
		Entity* e = entityManager_->addEntity();
		state_ = e->addComponent<GameState>();
		score_ = e->addComponent<Score>();
		score_->points_ = 0;
		
		entityManager_->setHandler<_hdlr_GameState>(e);
	}

	void update() override
	{
		if (!state_->running_)
		{
			auto ih = game_->getInputHandler();
			
			if (!state_->gameOver_)
			{
				if (ih->keyDownEvent())
				{
					entityManager_->getSystem<AsteroidsSystem>()->addAsteroids(10);
					state_->running_ = true;
				}
			}
			else
			{
				if (ih->keyDownEvent())
				{
					state_->gameOver_ = false;
					state_->win_ = false;
				}
			}
		}
	}

};

#endif // !__GAME_CTRL_SYSTEM_H__