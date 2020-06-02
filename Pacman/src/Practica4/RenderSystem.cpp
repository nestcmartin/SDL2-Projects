#include <cassert>

#include "Entity.h"
#include "EntityManager.h"

#include "Image.h"
#include "Transform.h"
#include "GameState.h"
#include "AnimatedImage.h"

#include "RenderSystem.h"

#include "Texture.h"

#include "SDL_Macros.h"

#include "ECS.h"
#include "SDLGame.h"


RenderSystem::RenderSystem() :
	System(ECS::_sys_Render) 
{
}

void RenderSystem::drawAnimatedEntity(Entity* e) 
{
	Transform* tr = e->getComponent<Transform>(ECS::Transform);
	AnimatedImage* img = e->getComponent<AnimatedImage>(
		ECS::AnimatedImageComponent);
	const auto& sprite = img->getSprite(game_->getTime());
	SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
	sprite.first->render(dest, tr->rotation_, sprite.second);
}

void RenderSystem::update() 
{
	auto gameState_ = enityManager_->getHandler(ECS::_hdlr_GameStateEntity)->getComponent<GameState>(ECS::GameState);

	drawFood(gameState_);
	drawGhosts(gameState_);
	drawPacMan(gameState_);
	drawState(gameState_);

}

void RenderSystem::drawFood(GameState* gs) 
{
	if (gs->state_ != GameState::RUNNING) return;

	for (auto& e : enityManager_->getGroup(ECS::_grp_Food)) 
	{
		drawAnimatedEntity(e);
	}
}

void RenderSystem::drawGhosts(GameState* gs) 
{
	if (gs->state_ != GameState::RUNNING) return;

	for (auto& e : enityManager_->getGroup(ECS::_grp_Ghost)) 
	{
		drawAnimatedEntity(e);
	}
}

void RenderSystem::drawPacMan(GameState* gs) 
{
	if (gs->state_ != GameState::RUNNING) return;

	drawAnimatedEntity(enityManager_->getHandler(ECS::_hdlr_PacManEntity));
}

void RenderSystem::drawState(GameState* gs) 
{
	// Score
	Texture scoreMsg(game_->getRenderer(), std::to_string(gs->score_), game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
	scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2, 10);

	if (gs->state_ == GameState::RUNNING) return;

	int x = 0;
	int y = 0;
	switch (gs->state_) 
	{
	case GameState::READY: 
	{
		auto startNewGameMsg = game_->getTextureMngr()->getTexture(Resources::PressEnterToStartANewGame);
		x = (game_->getWindowWidth() - startNewGameMsg->getWidth()) / 2;
		y = (game_->getWindowHeight() - startNewGameMsg->getHeight()) / 2;
		startNewGameMsg->render(x, y);
		
		break;
	}
	
	case GameState::OVER: 
	{
		auto toContMsg = game_->getTextureMngr()->getTexture(Resources::PressEnterToContinue);
		x = (game_->getWindowWidth() - toContMsg->getWidth()) / 2;
		y = (game_->getWindowHeight() - toContMsg->getHeight()) / 2;
		toContMsg->render(x, y);

		auto gameOverMsg = game_->getTextureMngr()->getTexture(Resources::GameOver);
		x = (game_->getWindowWidth() - gameOverMsg->getWidth()) / 2;
		y = (game_->getWindowHeight() - gameOverMsg->getHeight()) / 2 - 50;
		gameOverMsg->render(x, y);

		break;
	}

	default:
		assert(false);
		break;
	}
}