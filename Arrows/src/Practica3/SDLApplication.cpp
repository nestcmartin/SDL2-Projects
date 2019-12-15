#include "SDLApplication.h"

bool SDLApplication::exit_ = false;
GameStateMachine* SDLApplication::gameStateMachine_ = nullptr;

SDLApplication::SDLApplication() :
	error_(false),
	window_(nullptr),
	renderer_(nullptr)
{
	// Init SDL
	int res = SDL_Init(SDL_INIT_EVERYTHING);
	if (res > 0) throw SDLError(SDL_GetError());
	window_ = SDL_CreateWindow("Arrows", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) throw SDLError(SDL_GetError());
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) throw SDLError(SDL_GetError());
	TTF_Init();

	// Init sub-systems
	loadTextures();
	loadFonts();

	// Create Game State Machine
	gameStateMachine_ = new GameStateMachine();
	gameStateMachine_->pushState(new MainMenuState(this));
}

SDLApplication::~SDLApplication()
{
	// Delete Game State Machine
	delete gameStateMachine_;
	gameStateMachine_ = nullptr;

	// Clear Fonts
	for (std::pair<std::string, Font*> f : fonts_)
	{
		delete f.second;
		f.second = nullptr;
	}
	fonts_.clear();

	// Clear Textures
	for (std::pair<std::string, Texture*> t : textures_)
	{
		delete t.second; 
		t.second = nullptr;
	}
	textures_.clear();

	// Close SDL
	TTF_Quit();
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void SDLApplication::loadTextures()
{
	std::ifstream stream;
	stream.open(TEXTURES_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open" + TEXTURES_FILE + "\n");

	Uint32 numTextures = 0;
	std::string id, filename;
	int numRows, numCols;
	stream >> numTextures;

	for (Uint32 i = 0; i < numTextures; i++)
	{
		stream >> id >> filename >> numRows >> numCols;
		textures_[id] = new Texture(renderer_);
		textures_[id]->load(IMAGE_PATH + filename, numRows, numCols);		
	}

	stream.close();
}

void SDLApplication::loadFonts()
{
	std::ifstream stream;
	stream.open(FONTS_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open" + FONTS_FILE + "\n");

	Uint32 numFonts = 0;
	std::string id, filename;
	int size;
	stream >> numFonts;

	for (Uint32 i = 0; i < numFonts; i++)
	{
		stream >> id >> filename >> size;
		fonts_[id] = new Font();
		fonts_[id]->load(FONT_PATH + filename, size);
	}

	stream.close();
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

void SDLApplication::toMenuState(SDLApplication* app)
{
	while (gameStateMachine_->currentState()->getStateName() != "MENU_STATE")
	{
		gameStateMachine_->popState();
	}
}

void SDLApplication::toPlayState(SDLApplication* app)
{
	gameStateMachine_->pushState(new PlayState(app));
}

void SDLApplication::toPauseState(SDLApplication* app)
{
	gameStateMachine_->pushState(new PauseState(app));
}

void SDLApplication::toEndState(SDLApplication* app)
{
	int finalScore = static_cast<PlayState*>(gameStateMachine_->currentState())->getScore();
	bool win = static_cast<PlayState*>(gameStateMachine_->currentState())->isWon();
	gameStateMachine_->changeState(new EndState(app, finalScore, win));
}

void SDLApplication::closeApplication(SDLApplication* app)
{
	exit_ = true;
}

void SDLApplication::savePlayState(SDLApplication* app)
{
	int code;
	std::cout << "Introduce un código de guardado: "; std::cin >> code;
	gameStateMachine_->popState();
	static_cast<PlayState*>(gameStateMachine_->currentState())->saveToFile(code);
}

void SDLApplication::loadPlayState(SDLApplication* app)
{
	int code;
	std::cout << "Introduce tu código de carga: "; std::cin >> code;
	gameStateMachine_->pushState(new PlayState(app));
	static_cast<PlayState*>(gameStateMachine_->currentState())->loadFromFile(code);
}

void SDLApplication::resumeApplication(SDLApplication* app)
{
	gameStateMachine_->popState();
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