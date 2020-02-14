#include "SimpleMoveBahviour.h"
#include "Entity.h"
#include "Transform.h"

SimpleMoveBahviour::SimpleMoveBahviour() :
		Component(ecs::SimpleMoveBehavior) //
{
}

SimpleMoveBahviour::~SimpleMoveBahviour() {
}

void SimpleMoveBahviour::update() {
	Transform *tc = GETCMP2_(ecs::Transform,Transform);
	tc->setPos(tc->getPos() + tc->getVel());
}
