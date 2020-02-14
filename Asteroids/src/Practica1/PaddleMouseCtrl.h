#pragma once
#include "Component.h"
#include "Transform.h"

class PaddleMouseCtrl: public Component {
public:
	PaddleMouseCtrl();
	virtual ~PaddleMouseCtrl();

	void init() override;
	void update() override;
private:
	Transform *tr_;
};

