#ifndef __ARROW_H__
#define __ARROW_H__

#include "ArrowsGameObject.h"

class Game;
class Arrow : public ArrowsGameObject
{
public:
	static int numArrowsActive;
	
private:
	Uint32 numBalloonsBurst_;

public:
	Arrow(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Arrow();

	virtual void update();
	virtual SDL_Rect getCollisionRect() const;

	inline Uint32 getNumBallonsBurst() const { return numBalloonsBurst_; }
	inline void incrementNumBalloonsBurst() { numBalloonsBurst_++; }
};

#endif // !__ARROW_H__