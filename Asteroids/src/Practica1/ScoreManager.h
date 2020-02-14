#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:
	ScoreManager();
	ScoreManager(int rounds);
	virtual ~ScoreManager();

	int getLeftScore() const {
		return leftScore_;
	}

	void setLeftScore(int leftScore) {
		leftScore_ = leftScore;
	}

	int getRightScore() const {
		return rightScore_;
	}

	void setRightScore(int rightScore) {
		rightScore_ = rightScore;
	}

	int getRounds() const {
		return rounds_;
	}

	void setRounds(int rounds) {
		rounds_ = rounds;
	}

	bool isRunning() const {
		return running_;
	}

	void setRunning(bool running) {
		running_ = running;
	}

	bool isGameOver() {
		return leftScore_ == rounds_ || rightScore_ == rounds_;
	}

private:
	bool running_;
	int leftScore_;
	int rightScore_;
	int rounds_;
};
