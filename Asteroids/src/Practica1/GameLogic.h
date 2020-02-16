#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "Component.h"
#include "Transform.h"
#include "Health.h"
#include "BulletsPool.h"
#include "AsteroidsPool.h"
#include "ScoreManager.h"

class GameLogic : public Component 
{
private:
	Transform* fighterTransform_;
	Health* health_;
	BulletsPool* bulletsPool_;
	AsteroidsPool* asteroidsPool_;
	ScoreManager* scoreManager_;

public:
	GameLogic();
	GameLogic(AsteroidsPool* apool, BulletsPool* bpool, Health* health, Transform* fightertr);
	virtual ~GameLogic();
	
	void init() override;
	void update() override;
};

#endif // !__GAME_LOGIC_H__