#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a)
{
	direction_.rotate(angle_);
}

Arrow::~Arrow()
{
}

SDL_Rect Arrow::getCollisionRect() const
{
	Uint32 head = width_ / 4;
	
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX()) + (head * 3);
	rect.y = static_cast<int>(position_.getY());
	rect.w = head;
	rect.h = height_;

	return rect;
}