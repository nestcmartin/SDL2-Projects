#ifndef __GAME_CTRL_H__
#define __GAME_CTRL_H__

#include "Component.h"

#include "Transform.h"
#include "ScoreManager.h"

class GameCtrl : public Component 
{
public:
	GameCtrl();
	virtual ~GameCtrl();

	void init() override;
	void update() override;
	void draw() override;

private:
	ScoreManager* scoreManager_;
};

#endif // !__GAME_CTRL_H__