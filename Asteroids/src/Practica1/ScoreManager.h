#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

#include "Component.h"

class ScoreManager : public Component 
{
private:
	int score_;
	bool running_;
	bool gameOver_;
	bool win_;

public:
	ScoreManager();
	virtual ~ScoreManager();

	inline int getScore() const { return score_; }
	inline bool isRunning() const { return running_; }
	inline bool isGameOver() const { return gameOver_; }
	inline bool isWin() const { return win_; }
	inline void setScore(int score) { score_ = score; }
	inline void setRunning(bool running) { running_ = running; }
	inline void setGameOver(bool gameOver) { gameOver_ = gameOver; }
	inline void setWin(bool win) { win_ = win; }
};

#endif // !__SCORE_MANAGER_H__