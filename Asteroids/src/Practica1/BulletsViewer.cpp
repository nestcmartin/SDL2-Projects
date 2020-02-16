#include "BulletsViewer.h"
#include "SDL_Macros.h"
#include "Entity.h"

BulletsViewer::BulletsViewer() :
	Component(ECS::BulletsViewer),
	texture_(nullptr),
	bulletsPool_(nullptr)
{
}

BulletsViewer::BulletsViewer(Texture* texture) :
	Component(ECS::BulletsViewer),
	texture_(texture),
	bulletsPool_(nullptr)
{
}

BulletsViewer::~BulletsViewer()
{
}

void BulletsViewer::init()
{
	bulletsPool_ = GETCMP1_(BulletsPool);
}

void BulletsViewer::draw()
{
	std::vector<Bullet*> bullets = bulletsPool_->getPool();

	for (Bullet* b : bullets)
	{
		if (b->getActive())
		{
			double x = b->getPos().getX();
			double y = b->getPos().getY();
			double w = b->getW();
			double h = b->getH();
			double r = b->getRot();

			SDL_Rect dst = RECT(x, y, w, h);

			texture_->render(game_->getRenderer(), dst, r);
		}
	}
}
