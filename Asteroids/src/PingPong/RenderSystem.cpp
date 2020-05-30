#include "RenderSystem.h"
#include "Transform.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include <SDL.h>

#include "GameState.h"
#include "Score.h"
#include "Texture.h"
RenderSystem::RenderSystem() :
		System(ecs::_sys_Render) {
}

void RenderSystem::recieve(const msg::Message &msg) {
}

void RenderSystem::drawRectangle(Transform *tr) {
	SDL_Color color = { COLOR(0xffffffff) };

	SDL_Rect rect
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color));
	SDL_RenderFillRect(game_->getRenderer(), &rect);
}

void RenderSystem::drawCtrlMessages() {
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<
			GameState>(ecs::GameState);

	if (!gameState->ready_) {
		Texture *waiting = game_->getTextureMngr()->getTexture(
				Resources::WaitingForPlayer);
		waiting->render(
				game_->getWindowWidth() / 2 - waiting->getWidth() / 2,
				game_->getWindowHeight() - waiting->getHeight() - 50);

	} else if (!gameState->running_) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PressAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);

		// game over message when game is over
		if (gameState->currRound_ == gameState->maxRounds_) {
			Texture *gameOver = game_->getTextureMngr()->getTexture(
					Resources::GameOver);
			gameOver->render(
					game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
					game_->getWindowHeight() - gameOver->getHeight() - 150);
		}
	}
}

void RenderSystem::drawScore() {
	auto score = mngr_->getHandler(ecs::_hdlr_GameInfo)->getComponent<Score>(
			ecs::Score);

	Texture scoreTex(game_->getRenderer(),
			to_string(score->leftScore_) + " - "
					+ to_string(score->rightScore_),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::update() {

	auto ballTR = mngr_->getHandler(ecs::_hdlr_Ball)->getComponent<Transform>(
			ecs::Transform);

	auto leftPaddleTR = mngr_->getHandler(ecs::_hdlr_LeftPaddle)->getComponent<
			Transform>(ecs::Transform);

	auto rightPaddleTR =
			mngr_->getHandler(ecs::_hdlr_RightPaddle)->getComponent<Transform>(
					ecs::Transform);

	drawRectangle(ballTR);
	drawRectangle(leftPaddleTR);
	drawRectangle(rightPaddleTR);
	drawCtrlMessages();
	drawScore();

}

