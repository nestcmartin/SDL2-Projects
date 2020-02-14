#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"

class GameLogic: public Component {
public:
	GameLogic(Transform* ballTR, Transform* leftPaddleTR, Transform* rightPaddleTR);
	virtual ~GameLogic();
	void init() override;
	void update() override;
private:
	Transform* ballTR_;
	Transform* leftPaddleTR_;
	Transform* rightPaddleTR_;
	ScoreManager *scoreManager_;
};

