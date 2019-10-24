#ifndef __ARROW_H__
#define __ARROW_H__

#include "GameObject.h"

class Game;
class Arrow : public GameObject
{
public:
	Arrow(Game* g, Texture* t, Point2D p, int a, double s);
	~Arrow();

	virtual void update();

	SDL_Rect getArrowhead() const;
};



#endif // !__ARROW_H__
