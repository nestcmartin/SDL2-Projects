#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "GameObject.h"

class Game;
class Balloon : public GameObject
{
private:
	bool burst_;
	Uint32 burstTime_;

public:
	Balloon(Game* g, Texture* t, Point2D p);
	~Balloon();

	virtual void update();
};

#endif // !__BALLOON_H__
