#include "PingPong.h"

#include "SDL_macros.h"
using namespace std;

PingPong::PingPong(char *host, int port) :
		host_(host), //
		port_(port), //
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
}

PingPong::~PingPong() {
	closeGame();
}

void PingPong::initGame() {

	game_ = SDLGame::init("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);


	if ( !game_->getNetworking()->client(host_, port_) ) {
		throw "Couldn't connect to server!";
	}

	mngr_ = new Manager(game_);

	networkingSystem_ = mngr_->addSystem<NetworkingSystem>();
	physicsSystem_ = mngr_->addSystem<PhysicsSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	renderSystem_ = mngr_->addSystem<RenderSystem>();
}

void PingPong::closeGame() {
	delete mngr_;
}

void PingPong::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		physicsSystem_->update();
		renderSystem_->update();

		networkingSystem_->update();

		mngr_->flushMessages();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


