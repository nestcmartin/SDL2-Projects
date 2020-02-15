#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"

class GameLogic : public Component 
{
public:
	GameLogic();
	virtual ~GameLogic();
	
	void init() override;
	void update() override;

private:
	ScoreManager* scoreManager_;
};

#endif // !__GAME_LOGIC_H__