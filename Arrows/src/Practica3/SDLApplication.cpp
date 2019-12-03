#include "SDLApplication.h"

SDLApplication::SDLApplication() :
	window_(nullptr),
	renderer_(nullptr),
	gameStateMachine_(nullptr),
	exit_(false),
	error_(false)
{
	// Init SDL
	int res = SDL_Init(SDL_INIT_EVERYTHING);
	if (res > 0) throw SDLError(SDL_GetError());
	window_ = SDL_CreateWindow("Bow & Arrow 1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) throw SDLError(SDL_GetError());
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) throw SDLError(SDL_GetError());

	// Init Textures
	for (Uint32 i = 0; i < NUM_TEXTURES; i++)
	{
		textures_[i] = new Texture(renderer_);
		textures_[i]->load(IMAGE_PATH + textureAttributes[i].filename,
			textureAttributes[i].numRows, textureAttributes[i].numCols);
	}

	// Init Game State Machine
	gameStateMachine_ = new GameStateMachine();
}

SDLApplication::~SDLApplication()
{
	// Delete Game State Machine
	delete gameStateMachine_;
	gameStateMachine_ = nullptr;

	// Clear Textures
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete textures_[i]; 
		textures_[i] = nullptr;
	}

	// Close SDL
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void SDLApplication::run()
{
	while (!exit_)
	{
		Uint32 startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}
}

void SDLApplication::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit_)
	{
		gameStateMachine_->handleEvents(event);
		if (event.type == SDL_QUIT) exit_ = true;
	}
}

void SDLApplication::update()
{
	gameStateMachine_->update();
}

void SDLApplication::render() const
{
	SDL_RenderClear(renderer_);
	gameStateMachine_->render();
	SDL_RenderPresent(renderer_);
}