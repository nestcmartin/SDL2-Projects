#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

#include "Component.h"

class ScoreManager : public Component 
{
private:
	bool running_;

public:
	ScoreManager();
	virtual ~ScoreManager();

	inline bool isGameOver() { return true; }
	inline bool isRunning() const { return running_; }
	inline void setRunning(bool running) { running_ = running; }
};

#endif // !__SCORE_MANAGER_H__