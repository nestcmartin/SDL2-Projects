#include "SDL_macros.h"
#include "PingPong.h"
#include <assert.h>

#include "BallMoveBehaviour.h"
#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "PaddleKBCtrl.h"
#include "PaddleMouseCtrl.h"
#include "PaddleMoveBehaviour.h"
#include "Rectangle.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "SimpleMoveBahviour.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"

using namespace std;

PingPong::PingPong() :
		game_(nullptr), //
		entityManager_(nullptr), //
		exit_(false) {
	initGame();
}

PingPong::~PingPong() {
	closeGame();
}

void PingPong::initGame() {

	game_ = SDLGame::init("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity *leftPaddle = entityManager_->addEntity();
	Transform *leftPaddleTR = leftPaddle->addComponent<Transform>();
	leftPaddle->addComponent<PaddleKBCtrl>();
	leftPaddle->addComponent<PaddleMoveBehaviour>();
	leftPaddle->addComponent<Rectangle,SDL_Color>({COLOR(0xAA0000FF)});
	leftPaddleTR->setPos(5, game_->getWindowHeight() / 2 - 25);
	leftPaddleTR->setWH(10, 50);

	Entity *rightPaddle = entityManager_->addEntity();
	Transform *rightPaddleTR = rightPaddle->addComponent<Transform>();
	rightPaddle->addComponent<PaddleMouseCtrl>();
	rightPaddle->addComponent<PaddleMoveBehaviour>();
	rightPaddle->addComponent<Rectangle,SDL_Color>({COLOR(0x0000AAFF)});
	rightPaddleTR->setPos(game_->getWindowWidth() - 15,
			game_->getWindowHeight() / 2 - 25);
	rightPaddleTR->setWH(10, 50);

	Entity *ball = entityManager_->addEntity();
	Transform *ballTR = ball->addComponent<Transform>();
	ball->addComponent<BallMoveBehaviour>();
	ball->addComponent<Rectangle>();
	ballTR->setPos(game_->getWindowWidth() / 2 - 6,
			game_->getWindowHeight() / 2 - 6);
	ballTR->setWH(11, 11);

	Entity *gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>(1);
	gameManager->addComponent<GameLogic>(ballTR, leftPaddleTR, rightPaddleTR);
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>(GETCMP2(ball, Transform));
}

void PingPong::closeGame() {
	delete entityManager_;
}

void PingPong::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void PingPong::stop() {
	exit_ = true;
}

void PingPong::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void PingPong::update() {
	entityManager_->update();
}

void PingPong::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

