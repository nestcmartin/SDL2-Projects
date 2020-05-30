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
	System(ECS::_sys_Render)
{
}

void RenderSystem::init()
{
	playerNames_[manager_->getClientId()] = manager_->getName();
	playerNames_[1 - manager_->getClientId()] = "Anonymous";
	manager_->send<messages::PlayerName>(playerNames_[manager_->getClientId()]);
}

void RenderSystem::update()
{
	for (auto& e : manager_->getGroupEntities(ECS::_grp_Fighters))
	{
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto& e : manager_->getGroupEntities(ECS::_grp_Bullets))
	{
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	drawCtrlMessages();
	drawScore();
	drawNames();	
}

void RenderSystem::receive(const messages::Message& msg)
{
	switch (msg.id)
	{
	case messages::_PLAYER_NAME:
	{
		if (msg.senderClientId == manager_->getClientId()) return;
		playerNames_[msg.senderClientId] = static_cast<const messages::PlayerName&>(msg).name;
		break;
	}
	}
}

void RenderSystem::drawImage(Entity* e)
{
	if (!e->isActive()) return;

	Transform* tr = e->getComponent<Transform>(ECS::Transform);
	Texture* tex = e->getComponent<Image>(ECS::Image)->texture_;

	SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages()
{
	auto gameState = manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getState();

	if (gameState == GameCtrlSystem::WAITING)
	{
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2, (game_->getWindowHeight() - msgTex->getHeight() - 10));
	}
	else if (gameState != GameCtrlSystem::RUNNING)
	{
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::PressEnterKey);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2, (game_->getWindowHeight() - msgTex->getHeight() - 10));

		if (gameState == GameCtrlSystem::GAMEOVER)
		{
			Texture* gameOverMsgTex = nullptr;

			if (manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getScore(manager_->getClientId()) < 3)
			{
				gameOverMsgTex = game_->getTextureMngr()->getTexture(Resources::GameOverLose);
			}
			else if (manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getScore(manager_->getClientId()) == 3)
			{
				if (manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl)->getScore(1 - manager_->getClientId()) == 3)
				{
					gameOverMsgTex = game_->getTextureMngr()->getTexture(Resources::GameOverDraw);
				}
				else
				{
					gameOverMsgTex = game_->getTextureMngr()->getTexture(Resources::GameOverWin);
				}
			}

			gameOverMsgTex->render((game_->getWindowWidth() - gameOverMsgTex->getWidth()) / 2, (game_->getWindowHeight() - gameOverMsgTex->getHeight()) / 2);
		}
	}
}

void RenderSystem::drawScore()
{
	auto gameCtrl = manager_->getSystem<GameCtrlSystem>(ECS::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(), to_string(gameCtrl->getScore(0)) + " - " + to_string(gameCtrl->getScore(1)), game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::drawNames()
{
	SDL_Rect dest;
	auto bg = game_->getTextureMngr()->getTexture(Resources::Bullet);
	Texture playerNameTex(game_->getRenderer(), playerNames_[manager_->getClientId()], game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });
	Texture oponentNameTex(game_->getRenderer(), playerNames_[1 - manager_->getClientId()], game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });

	if (manager_->getClientId() == 0)
	{
		dest = RECT(10, 10, playerNameTex.getWidth(), playerNameTex.getHeight());
		oponentNameTex.render(game_->getWindowWidth() - playerNameTex.getWidth() - 10, 10);
	}
	else
	{
		dest = RECT(game_->getWindowWidth() - playerNameTex.getWidth() - 10, 10, playerNameTex.getWidth(), playerNameTex.getHeight());
		oponentNameTex.render(10, 10);
	}

	bg->render(dest);
	playerNameTex.render(dest.x, dest.y);
}
