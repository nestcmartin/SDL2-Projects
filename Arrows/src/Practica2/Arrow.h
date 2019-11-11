#ifndef __ARROW_H__
#define __ARROW_H__

#include "ArrowsGameObject.h"

class Game;
class Arrow : public ArrowsGameObject
{
public:
	Arrow(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Arrow();

	virtual SDL_Rect getCollisionRect() const;
};

#endif // !__ARROW_H__