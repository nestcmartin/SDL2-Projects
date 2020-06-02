#ifndef __PACMAN_SYSTEM_H__
#define __PACMAN_SYSTEM_H__

#include "Entity.h"
#include "Transform.h"
#include "System.h"

class PacManSystem : public System 
{
private:
	Entity* pacman_;
	Transform* transform_;

public:
	PacManSystem();

	void init() override;
	void update() override;
	void receive(const msg::Message& msg) override;

private:
	void resetPacManPosition();
};

#endif // !__PACMAN_SYSTEM_H__