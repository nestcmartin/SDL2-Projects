#include "ScoreManager.h"

ScoreManager::ScoreManager() :
		ScoreManager(5) {
}

ScoreManager::ScoreManager(int rounds) :
		Component(ecs::ScoreManager), //
		running_(false), //
		leftScore_(0), //
		rightScore_(0), //
		rounds_(rounds) //
{
}

ScoreManager::~ScoreManager() {
}

