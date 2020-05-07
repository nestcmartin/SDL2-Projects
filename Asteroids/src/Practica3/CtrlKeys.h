#ifndef __CTRL_KEYS_H__
#define __CTRL_KEYS_H__

#include <SDL_keyboard.h>

#include "Component.h"

struct CtrlKeys : Component 
{
	CtrlKeys() :
		Component(ECS::CtrlKeys),
		left_(SDLK_LEFT),
		right_(SDLK_RIGHT),
		speedup_(SDLK_UP),
		slowdown_(SDLK_DOWN),
		shoot_(SDLK_SPACE),
		lastShootTime_(0)
	{
	}

	CtrlKeys(SDL_Keycode left, SDL_Keycode right, SDL_Keycode speedup, SDL_Keycode slowdown, SDL_Keycode shoot) :
		Component(ECS::CtrlKeys),
		left_(left), 
		right_(right), 
		speedup_(speedup), 
		slowdown_(slowdown), 
		shoot_(shoot), 
		lastShootTime_(0) 
	{
	}

	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode speedup_;
	SDL_Keycode slowdown_;
	SDL_Keycode shoot_;
	Uint32 lastShootTime_;
};

#endif // !__CTRL_KEYS_H__