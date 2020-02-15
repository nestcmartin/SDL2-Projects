#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <SDL_rect.h>

#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

class Rectangle : public Component 
{
private:
	SDL_Color color_;
	Transform* transform_;

public:
	Rectangle();
	Rectangle(SDL_Color color);
	virtual ~Rectangle();

	void init() override;
	void draw() override;
};

#endif // !__RECTANGLE_H__