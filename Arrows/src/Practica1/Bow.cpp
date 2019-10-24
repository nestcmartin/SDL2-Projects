#include "Bow.h"
#include "Game.h"

Bow::Bow(Game* _g, Texture* _t, Point2D _p, Uint32 _w, Uint32 _h, double _s) :
	p(_p),
	d({ 0, 0 }),
	v({ 0, 0 }),
	s(_s),
	a(0),
	w(_w),
	h(_h),
	drawTime_(0),
	sprite(_t),
	arrow_(nullptr),
	game(_g),
	armed_(false)
{
}

Bow::~Bow()
{
}

void Bow::charge()
{
	if (!armed_ && game->hasArrows())
	{
		drawTime_ = SDL_GetTicks();
		armed_ = true;
	}
}

void Bow::loose()
{
	if (armed_)
	{
		double drawFactor = 1.0 + ((SDL_GetTicks() - drawTime_) / 10000.0);
		arrow_ = new Arrow(game->getTexture(Game::ARROW), 
					  { p.getX(), p.getY() + (h / 2) },
					  ARROW_WIDTH, ARROW_HEIGHT, ARROW_SPEED * drawFactor, a);
		game->shootArrow(arrow_);
		armed_ = false;
	}
}

SDL_Rect Bow::getRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(p.getX());
	rect.y = static_cast<int>(p.getY());
	rect.w = w;
	rect.h = h;
	return rect;
}

void Bow::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT) charge();
		else if (event.key.keysym.sym == SDLK_RIGHT) loose();
		else if (event.key.keysym.sym == SDLK_UP) d = Vector2D(0, -1);
		else if (event.key.keysym.sym == SDLK_DOWN) d = Vector2D(0, 1);
		else if (event.key.keysym.sym == SDLK_a) a -= 3;
		else if (event.key.keysym.sym == SDLK_d) a += 3;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP ||
			event.key.keysym.sym == SDLK_DOWN)
		{
			d = Vector2D(0, 0);
		}
	}
}

void Bow::update()
{
	v = d * s;
	
	// Limit y-axis movement
	if ((p + v).getY() < 0.0 ||
		(p + v).getY() > (WIN_HEIGHT - BOW_HEIGHT)) return;

	// Limit rotation
	if (a > 60) a = 60;
	if (a < -60) a = -60;
	
	p = p + v;
}

void Bow::render() const
{
	sprite->renderFrame(getRect(), 0, 0, a);
	if (armed_)
	{
		game->getTexture(Game::ARROW)->renderFrame({ static_cast<int>(p.getX()), 
												  static_cast<int>(p.getY() + (h / 2)), 
												  ARROW_WIDTH, ARROW_HEIGHT }, 0, 0, a);
	}
}

void Bow::saveState(std::ofstream& stream)
{
	stream << p << " " << a << std::endl;
}

void Bow::loadState(std::ifstream& stream)
{
	stream >> p >> a;
}
