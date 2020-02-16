#ifndef __GAME_CTRL_H__
#define __GAME_CTRL_H__

#include "Component.h"
#include "AsteroidsPool.h"
#include "Health.h"
#include "ScoreManager.h"

class GameCtrl : public Component 
{
private:
	Health* health_;
	ScoreManager* scoreManager_;
	AsteroidsPool* asteroidsPool_;

public:
	GameCtrl();
	GameCtrl(Health* health, AsteroidsPool* pool);
	virtual ~GameCtrl();

	void init() override;
	void update() override;
	void draw() override;
};

#endif // !__GAME_CTRL_H__