#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "EntityManager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
		System(ECS::_sys_Render) {
}

void RenderSystem::update() {
	for (auto &e : manager_->getGroupEntities(ECS::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto &e : manager_->getGroupEntities(ECS::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
}

void RenderSystem::drawImage(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ECS::Transform);
	Texture *tex = e->getComponent<Image>(ECS::Image)->texture_;

	SDL_Rect dest =
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() 
{
	auto gameState = manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getState();

	if (gameState == GameCtrlSystem::WAITING)
	{
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}
	else if (gameState != GameCtrlSystem::RUNNING) 
	{
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::PressEnterKey);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));

		if (gameState == GameCtrlSystem::GAMEOVER) 
		{
			auto msgTex = game_->getTextureMngr()->getTexture(Resources::GameOver);
			msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight()) / 2);
		}
	}
}

void RenderSystem::drawScore() {
	auto gameCtrl = manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}
