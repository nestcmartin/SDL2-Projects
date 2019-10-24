#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Game* _g, Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s) :
	p(_p),
	d({ 0, -1 }),
	v({ 0, 0 }),
	w(_w),
	h(_h),
	c(0),
	sprite(_t),
	game(_g),
	active(true),
	burst_(false),
	burstTime_(0)
{
	r = rand() % sprite->getNumRows();
	s = BALLOON_MIN_SPEED + 
		static_cast<float>(rand()) / 
		(static_cast<float>(RAND_MAX / 
		(BALLOON_MAX_SPEED - BALLOON_MIN_SPEED)));
}

Balloon::~Balloon()
{
}

SDL_Rect Balloon::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(p.getX());
	rect.y = static_cast<int>(p.getY());
	rect.w = w;
	rect.h = h;
	return rect;
}

void Balloon::update()
{
	if (!burst_)
	{
		v = d * s;
		p = p + v;

		burst_ = game->checkCollision(this);
		if (burst_)
		{
			burstTime_ = SDL_GetTicks();
			c++;
		}

		active = p.getY() > -static_cast<int>(h);
	}
	else
	{
		Uint32 elapsedTime = SDL_GetTicks() - burstTime_;
		if (c < 6 && (elapsedTime > FRAME_TIME * c)) c++;
		active = c < 6;
	}
}

void Balloon::render() const
{
	sprite->renderFrame(getRect(), r, c);
}

void Balloon::saveState(std::ofstream& stream)
{
	if (!burst_)
	{
		stream << p << " " << s << " " << r << std::endl;
	}
}

void Balloon::loadState(std::ifstream& stream)
{
	stream >> p >> s >> r;
}
