#include "Component.h"

Component::Component(ECS::ComponentId id) :
	entity_(nullptr),
	game_(nullptr),
	id_(id)
{
}

Component::~Component() 
{
}
