#include "Arrow.h"
#include "GameState.h"
#include "PlayState.h"

int Arrow::count = 0;

Arrow::Arrow(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	numHits_(1)
{
	direction_.rotate(angle_);
	count++;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	ArrowsGameObject::update();

	if (position_.getX() > WIN_WIDTH || position_.getY() > WIN_HEIGHT || position_.getY() < 0)
	{
		count--;
		static_cast<PlayState*>(state_)->killArrow(iterator_);
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