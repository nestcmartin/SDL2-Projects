#pragma once

#include "Component.h"

class SimpleMoveBahviour: public Component {
public:
	SimpleMoveBahviour();
	virtual ~SimpleMoveBahviour();
	void update() override;
};

