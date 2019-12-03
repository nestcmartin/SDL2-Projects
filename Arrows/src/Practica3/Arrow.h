#ifndef __ARROW_H__
#define __ARROW_H__

#include "ArrowsGameObject.h"

class GameState;
class Arrow : public ArrowsGameObject
{
public:
	static int count;

private:
	Uint32 numHits_;

public:
	Arrow(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Arrow();

	virtual void update();
	virtual SDL_Rect getCollisionRect() const;

	inline Uint32 getNumHits() const { return numHits_; }
	inline void addHit() { numHits_++; }

};

#endif // !__ARROW_H__