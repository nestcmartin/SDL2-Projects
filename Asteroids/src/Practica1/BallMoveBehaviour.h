#pragma once

#include "Component.h"
#include "Transform.h"

class BallMoveBehaviour: public Component {
public:
	BallMoveBehaviour();
	virtual ~BallMoveBehaviour();
	void init() override;
	void update() override;
private:
	Transform *tr_;
};

