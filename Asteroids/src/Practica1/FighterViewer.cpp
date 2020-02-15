#include "FighterViewer.h"
#include "SDL_Macros.h"
#include "Entity.h"

FighterViewer::FighterViewer() :
	Component(ECS::FighterViewer),
	texture_(nullptr)
{
}

FighterViewer::FighterViewer(Texture* texture) :
	Component(ECS::FighterViewer),
	texture_(texture)
{
}

FighterViewer::~FighterViewer()
{
}

void FighterViewer::init()
{
	transform_ = GETCMP1_(Transform);
}

void FighterViewer::draw()
{
	double x = transform_->getPos().getX();
	double y = transform_->getPos().getY();
	double w = transform_->getW();
	double h = transform_->getH();
	double r = transform_->getRot();
	
	SDL_Rect dst = RECT(x, y, w, h);
	SDL_Rect src = RECT(47, 90, 207, 250);

	texture_->render(game_->getRenderer(), dst, r, &src);
}