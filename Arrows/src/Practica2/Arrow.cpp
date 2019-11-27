#include "Arrow.h"
#include "Game.h"

int Arrow::numArrowsActive = 0;

Arrow::Arrow(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a)
{
	direction_.rotate(angle_);
	numArrowsActive++;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	ArrowsGameObject::update();
	if (position_.getX() > WIN_WIDTH)
	{
		numArrowsActive--;
		game_->killGameObject(iterator_);
	}
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