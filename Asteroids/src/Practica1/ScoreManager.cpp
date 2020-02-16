#include "ScoreManager.h"

ScoreManager::ScoreManager() :
	Component(ECS::ScoreManager),
	score_(0),
	running_(false),
	gameOver_(false),
	win_(false)
{
}

ScoreManager::~ScoreManager()
{
}

