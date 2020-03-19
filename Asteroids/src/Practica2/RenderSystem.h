#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "Entity.h"
#include "EntityManager.h"

#include "Health.h"
#include "Score.h"
#include "Transform.h"
#include "ImageComponent.h"
#include "GameState.h"

#include "System.h"

#include "ECS.h"
#include "Texture.h"
#include "SDLGame.h"
#include "SDL_Macros.h"

class RenderSystem : public System
{
private:
	SDL_Rect fighterSrcRect_ = RECT(47, 90, 207, 250);

public:
	void draw(Entity* e)
	{
		Transform* tr = e->getComponent<Transform>();
		ImageComponent* img = e->getComponent<ImageComponent>();
		Health* health = e->getComponent<Health>();

		SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);

		if (health != nullptr)
		{
			img->texture_->render(dest, tr->rotation_, &fighterSrcRect_);

			for (int i = 0; i < health->numLives_; i++)
			{
				health->texture_->render(game_->getRenderer(),
					20 + ((health->texture_->getWidth() + 10) * i), 20);
			}
		}
		else
		{
			img->texture_->render(dest, tr->rotation_);
		}
	}

	void drawScore()
	{
		auto sc = entityManager_->getHandler<_hdlr_GameState>()->getComponent<Score>();
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_), game_->getFontManager()->getFont(Resources::ARIAL24), { COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2, 10);
	}

	void drawMsg()
	{
		if (!entityManager_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->running_)
		{
			if (entityManager_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->gameOver_)
			{
				Texture* gameOver;
				if (entityManager_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->win_) gameOver = game_->getTextureManager()->getTexture(Resources::GameOverWin);
				else gameOver = game_->getTextureManager()->getTexture(Resources::GameOverLose);
				gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2, game_->getWindowHeight() - gameOver->getHeight() - 150);
			}
			else
			{
				Texture* hitanykey = game_->getTextureManager()->getTexture(Resources::PresAnyKey);
				hitanykey->render(game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2, game_->getWindowHeight() - hitanykey->getHeight() - 50);
			}
		}
	}

	void update() override
	{
		for (auto& e : entityManager_->getGroupEntities<_grp_Asteroid>()) draw(e);
		for (auto& e : entityManager_->getGroupEntities<_grp_Bullet>()) draw(e);
		draw(entityManager_->getHandler<_hdlr_Fighter>());
		drawScore();
		drawMsg();
	}
};

#endif // !__RENDER_SYSTEM_H__