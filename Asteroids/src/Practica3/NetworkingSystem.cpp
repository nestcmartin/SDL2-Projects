#include "EntityManager.h"

#include "NetworkingSystem.h"

#include "Messages.h"

NetworkingSystem::NetworkingSystem() :
	System(ECS::_sys_NetWorking) 
{

}

NetworkingSystem::~NetworkingSystem() 
{
}

void NetworkingSystem::receive(const MSG::Message& msg) 
{
	if (msg.senderClientId == entityManager_->getClientId()) 
	{
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() 
{
	auto net = game_->getNetworking();
	MSG::Message* msg = nullptr;

	while ((msg = net->receive()) != nullptr) 
	{
		switch (msg->id) 
		{
		case MSG::_CLIENT_DISCONNECTED:
			entityManager_->forwardMsg<MSG::ClientDisconnectedMsg>(msg->senderClientId, static_cast<MSG::ClientDisconnectedMsg*>(msg)->clientId);
			break;

		default:
			assert(false);
			break;
		}
	}
}
