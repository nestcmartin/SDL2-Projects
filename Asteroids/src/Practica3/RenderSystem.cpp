#include "EntityManager.h"

#include "Image.h"
#include "Transform.h"

#include "RenderSystem.h"
#include "GameCtrlSystem.h"

#include "Texture.h"

#include "ECS.h"
#include "SDLGame.h"
#include "SDL_Macros.h"

RenderSystem::RenderSystem() :
	System(ECS::_sys_Render) 
{
}

void RenderSystem::update() 
{
	for (auto& e : entityManager_->getGroupEntities(ECS::_grp_Fighters)) 
	{
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto& e : entityManager_->getGroupEntities(ECS::_grp_Bullets))
	{
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	drawCtrlMessages();
	drawScore();
}

void RenderSystem::drawImage(Entity* e) 
{
	Transform* tr = e->getComponent<Transform>(ECS::Transform);
	Texture* tex = e->getComponent<Image>(ECS::Image)->texture_;
	SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() 
{
	auto gameState = entityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getState();

	if (gameState != GameCtrlSystem::RUNNING) 
	{
		auto msgTex = game_->getTextureManager()->getTexture(Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2, (game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::GAMEOVER) 
	{
		auto msgTex = game_->getTextureManager()->getTexture(Resources::GameOver);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2, (game_->getWindowHeight() - msgTex->getHeight()) / 2);
	}
}

void RenderSystem::drawScore() 
{
	auto gameCtrl = entityManager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(), 
		std::to_string(gameCtrl->getScore(0)) + " - " + std::to_string(gameCtrl->getScore(1)), 
		game_->getFontManager()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });

	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}
