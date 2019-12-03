#ifndef __SDL_GAME_OBJECT_H__
#define __SDL_GAME_OBJECT_H__

#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class GameState;
class SDLGameObject : public GameObject
{
protected:
	GameState* state_;
	Texture* texture_;
	Uint32 width_;
	Uint32 height_;
	Point2D position_;

public:
	virtual ~SDLGameObject();

	virtual void update() = 0;
	virtual void render() const = 0;

protected:
	SDLGameObject(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p);
};

#endif // !__SDL_GAME_OBJECT_H__