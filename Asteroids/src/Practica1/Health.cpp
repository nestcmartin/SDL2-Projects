#include "Health.h"

Health::Health() :
	Component(ECS::Health),
	texture_(nullptr),
	numLives_(0)
{
}

Health::Health(Texture* texture) :
	Component(ECS::Health),
	texture_(texture),
	numLives_(0)
{
}

Health::~Health()
{
}

void Health::init()
{
	numLives_ = MAX_NUM_LIVES;
}

void Health::draw()
{
	for (int i = 0; i < numLives_; i++)
	{
		texture_->render(game_->getRenderer(), 20 + ((texture_->getWidth() + 10) * i), 20);
	}
}