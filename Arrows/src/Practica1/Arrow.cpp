#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s, int _a) :
	p(_p),
	d({1, 0}),
	v({0, 0}),
	s(_s),
	a(_a),
	w(_w),
	h(_h),
	sprite(_t),
	active(true)
{
	d.rotate(a);
}

Arrow::~Arrow()
{
}

SDL_Rect Arrow::getArrowhead() const
{
	// The arrowhead is the 4th quarter of the texture
	Uint32 head = w / 4;
	
	SDL_Rect rect;
	rect.x = static_cast<int>(p.getX()) + (head * 3);
	rect.y = static_cast<int>(p.getY());
	rect.w = head;
	rect.h = h;

	return rect;
}

SDL_Rect Arrow::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(p.getX());
	rect.y = static_cast<int>(p.getY());
	rect.w = w;
	rect.h = h;
	return rect;
}

void Arrow::update()
{
	v = d * s;
	p = p + v;

	active = p.getX() < WIN_WIDTH &&
		     p.getY() < WIN_HEIGHT &&
		     p.getY() > 0;
}

void Arrow::render() const
{
	sprite->renderFrame(getRect(), 0, 0, a);
}

void Arrow::saveState(std::ofstream& stream)
{
	stream << p << " " << d << " " << s << " " << a << std::endl;
}

void Arrow::loadState(std::ifstream& stream)
{
	stream >> p >> d >> s >> a;
}
