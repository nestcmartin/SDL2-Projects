#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "Entity.h"
#include "System.h"

class RenderSystem : public System 
{
private:
	const char* playerNames_[2];

public:
	RenderSystem();
	
	void init() override;
	void update() override;
	void receive(const messages::Message& msg) override;

private:
	void drawImage(Entity* e);
	void drawCtrlMessages();
	void drawScore();
	void drawNames();
};

#endif // !__RENDER_SYSTEM_H__