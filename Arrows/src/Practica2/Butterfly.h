#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__

#include "ArrowsGameObject.h"

class Game;
class Butterfly : public ArrowsGameObject
{
public:
	Butterfly(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Butterfly();

	virtual void update();
	virtual void render() const;
};

#endif // !__BUTTERFLY_H__

