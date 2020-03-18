#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "System.h"

#include "ECS.h"
#include "Entity.h"
#include "EntityManager.h"

#include "Texture.h"
#include "SDLGame.h"
#include "SDL_Macros.h"

#include "Score.h"
#include "Transform.h"
#include "ImageComponent.h"

class RenderSystem : public System 
{
public:

	void draw(Entity* e) 
	{
		Transform* tr = e->getComponent<Transform>();
		ImageComponent* img = e->getComponent<ImageComponent>();
		SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
		img->texture_->render(dest, tr->rotation_);
	}

	void drawScore() 
	{
		auto sc = entityManager_->getHandler<_hdlr_GameState>()->getComponent<Score>();
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_), game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2, 10);

	}

	void update() override 
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Star>()) 
		{
			draw(e);
		}

		draw(entityManager_->getHandler<_hdlr_PacMan>());

		drawScore();

		Texture msg(game_->getRenderer(), "Press ENTER to add More Stars", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
		msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
	}
};

#endif // !__RENDER_SYSTEM_H__