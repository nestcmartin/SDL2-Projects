#ifndef __NETWORKING_SYSTEM_H__
#define __NETWORKING_SYSTEM_H__

#include "System.h"

class NetworkingSystem : public System
{
public:
	NetworkingSystem();
	virtual ~NetworkingSystem();

	void receive(const MSG::Message& msg) override;
	void update() override;
};

#endif // !__NETWORKING_SYSTEM_H__