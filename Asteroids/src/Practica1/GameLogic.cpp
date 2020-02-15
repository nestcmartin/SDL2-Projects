#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic() :
	Component(ECS::GameLogic),
	scoreManager_(nullptr)
{
}

GameLogic::~GameLogic() 
{
}

void GameLogic::init() 
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() 
{
}