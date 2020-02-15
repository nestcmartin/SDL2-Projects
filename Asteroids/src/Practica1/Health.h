#ifndef __HEALTH_H__
#define __HEALTH_H__

#include <algorithm>

#include "Texture.h"
#include "Component.h"

class Health : public Component
{
private:
	const int MAX_NUM_LIVES = 3;

	int numLives_;
	Texture* texture_;

public:
	Health();
	Health(Texture* texture);
	virtual ~Health();

	inline int getLives() const { return numLives_; }
	
	void init() override;
	void draw() override;

	void loseHealth() { numLives_ = std::max(numLives_ - 1, 0); }
	void resetHealth() { numLives_ = MAX_NUM_LIVES; }
};

#endif // !__HEALTH_H__
