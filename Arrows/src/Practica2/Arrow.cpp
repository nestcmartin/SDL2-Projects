#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Game* g, Texture* t, Point2D p, int a, double s) :
	GameObject(g, t, p, ARROW_DIR, ARROW_WIDTH, ARROW_HEIGHT, a, s)
{
	direction_.rotate(a);
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	GameObject::update();
	setActive(position_.getX() < WIN_WIDTH &&
		position_.getY() < WIN_HEIGHT &&
		position_.getY() > 0);
}

SDL_Rect Arrow::getArrowhead() const
{
	SDL_Rect arrowheadRect;
	Uint32 arrowheadWidth = width_ / 4;
	arrowheadRect.x = static_cast<int>(position_.getX()) + (arrowheadWidth * 3);
	arrowheadRect.y = static_cast<int>(position_.getY());
	arrowheadRect.w = arrowheadWidth;
	arrowheadRect.h = height_;
	return arrowheadRect;
}