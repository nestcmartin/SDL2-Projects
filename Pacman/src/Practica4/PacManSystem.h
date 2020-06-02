#ifndef __PACMAN_SYSTEM_H__
#define __PACMAN_SYSTEM_H__


#include "System.h"
#include "Transform.h"
#include "Entity.h"

class PacManSystem : public System 
{
private:
	Entity* pacman_;
	Transform* transform_;

public:
	PacManSystem();

	void init() override;
	void update() override;

	// TODO: privatize this
	void resetPacManPosition();
};

#endif // !__PACMAN_SYSTEM_H__