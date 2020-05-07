#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "Entity.h"

#include "System.h"

class RenderSystem : public System 
{
public:
	RenderSystem();
	
	void update() override;

private:
	void drawImage(Entity* e);
	void drawCtrlMessages();
	void drawScore();
};

#endif // !__RENDER_SYSTEM_H__