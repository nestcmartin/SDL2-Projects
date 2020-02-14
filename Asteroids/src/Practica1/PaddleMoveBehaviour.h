#pragma once

#include "Component.h"
#include "Transform.h"

class PaddleMoveBehaviour: public Component {
public:
	PaddleMoveBehaviour();
	virtual ~PaddleMoveBehaviour();
	void init() override;
	void update() override;
private:
	Transform *tr_;
};

