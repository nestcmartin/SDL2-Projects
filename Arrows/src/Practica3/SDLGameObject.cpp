#include "SDLGameObject.h"
#include "GameState.h"

SDLGameObject::SDLGameObject(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p) : 
	GameObject(),
	state_(g),
	texture_(t),
	width_(w),
	height_(h),
	position_(p)
{
}

SDLGameObject::~SDLGameObject()
{
}

SDL_Rect SDLGameObject::getDestRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX());
	rect.y = static_cast<int>(position_.getY());
	rect.w = width_;
	rect.h = height_;
	return rect;
}