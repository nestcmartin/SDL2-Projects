#include "AsteroidsViewer.h"
#include "SDL_Macros.h"
#include "Entity.h"

AsteroidsViewer::AsteroidsViewer() :
	Component(ECS::AsteroidsViewer),
	texture_(nullptr),
	asteroidsPool_(nullptr)
{
}

AsteroidsViewer::AsteroidsViewer(Texture* texture) :
	Component(ECS::AsteroidsViewer),
	texture_(texture),
	asteroidsPool_(nullptr)
{
}

AsteroidsViewer::~AsteroidsViewer()
{
}

void AsteroidsViewer::init()
{
	asteroidsPool_ = GETCMP1_(AsteroidsPool);
}

void AsteroidsViewer::draw()
{
	std::vector<Asteroid*> asteroids = asteroidsPool_->getPool();

	for (Asteroid* a : asteroids)
	{
		if (a->getActive())
		{
			double x = a->getPos().getX();
			double y = a->getPos().getY();
			double w = a->getW();
			double h = a->getH();
			double r = a->getRot();

			SDL_Rect dst = RECT(x, y, w, h);

			texture_->render(game_->getRenderer(), dst, r);
		}
	}
}
