#pragma once
#include "ecs.h"
#include "System.h"
#include "Transform.h"



class RenderSystem: public System {
public:
	RenderSystem();
	void recieve(const msg::Message &msg) override;
	void update() override;
private:
	void drawRectangle(Transform* tr);
	void drawCtrlMessages();
	void drawScore();

};


