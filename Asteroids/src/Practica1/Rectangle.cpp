#include "Rectangle.h"

Rectangle::Rectangle() :
	Rectangle({ COLOR(0xFFFFFFFF) }) 
{
}

Rectangle::Rectangle(SDL_Color color) :
	Component(ECS::Rectangle),
	color_(color),
	transform_(nullptr) 
{
}

Rectangle::~Rectangle() 
{
}

void Rectangle::init() 
{
	transform_ = GETCMP1_(Transform);
}

void Rectangle::draw()
{
	SDL_Rect rect RECT(transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH());
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
	SDL_RenderFillRect(game_->getRenderer(), &rect);
}