#include "Game.h"

Game::Game() :
	bow(nullptr),
	window_(nullptr),
	renderer_(nullptr),
	scoreBoard_(nullptr),
	end_(false),
	exit_(false),
	score_(0),
	arrowsLeft(NUM_ARROWS),
	lastSpawnTime_(0) 
{
	initSDL();
	loadTextures();
	loadEntities();
}
Game::~Game()
{
	clearScene();
	clearTextures();
	closeSDL();
}

void Game::initSDL()
{
	int res = SDL_Init(SDL_INIT_EVERYTHING);
	if (res > 0) throw SDLError(SDL_GetError());

	window_ = SDL_CreateWindow("Bow & Arrow 1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) throw SDLError(SDL_GetError());

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) throw SDLError(SDL_GetError());
}
void Game::loadTextures()
{
	for (Uint32 i = 0; i < NUM_TEXTURES; i++)
	{
		textures[i] = new Texture(renderer_);
		textures[i]->load(IMAGE_PATH + textureAttributes[i].filename,
			textureAttributes[i].numRows, textureAttributes[i].numCols);
	}
}
void Game::loadEntities()
{
	bow = new Bow(this, textures[BOW], { 50, WIN_HEIGHT / 2 });
	scoreBoard_ = new ScoreBoard(this, textures[ARROW_UI], textures[DIGITS]);
}

void Game::clearScene()
{
	for (Arrow* a : arrows)
	{
		delete a; a = nullptr;
	}
	arrows.clear();

	for (Balloon* b : balloons)
	{
		delete b; b = nullptr;
	}
	balloons.clear();

	delete scoreBoard_; scoreBoard_ = nullptr;
	delete bow; bow = nullptr;
}
void Game::clearTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete textures[i]; textures[i] = nullptr;
	}
}
void Game::closeSDL()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::spawnBallon()
{
	Uint32 elapsedTime = SDL_GetTicks() - lastSpawnTime_;
	if (elapsedTime > SPAWN_TIME)
	{
		Uint32 rndx = rand() % SPAWN_SPACE + SPAWN_LOWER_BOUND;
		balloons.push_back(new Balloon(this, textures[BALLOONS], 
						   { static_cast<double>(rndx), WIN_HEIGHT }));
		lastSpawnTime_ = SDL_GetTicks();
	}
}
void Game::shootArrow(Arrow* a)
{
	arrows.push_back(a);
	arrowsLeft--;
}
bool Game::checkCollision(Balloon* b)
{
	bool collision = false;
	SDL_Rect B = b->getRect();

	auto it = arrows.begin();
	while (it != arrows.end() && !collision)
	{
		if ((*it)->isActive())
		{
			SDL_Rect A = (*it)->getArrowhead();
			collision = SDL_HasIntersection(&A, &B);
		}
		it++;
	}

	if (collision) score_ += 10;
	return collision;
}

void Game::run()
{
	while (!exit_ && !end_)
	{
		Uint32 startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}

	if (end_) scoreBoard_->registerPlayerScore();
}
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit_)
	{
		if (event.type == SDL_QUIT)
		{
			exit_ = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				exit_ = true;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				saveState();
			}
			if (event.key.keysym.sym == SDLK_l)
			{
				clearScene();
				loadState();
			}
		}

		bow->handleEvents(event);
	}
}
void Game::update()
{
	spawnBallon();
	if (bow) bow->update();
	for (Arrow* a : arrows) if (a->isActive()) a->update();
	for (Balloon* b : balloons) if (b->isActive()) b->update();
	if (scoreBoard_) scoreBoard_->update();

	// End game
	Uint32 activeArrows = 0;
	for (Arrow* a : arrows) if (a->isActive()) activeArrows++;
	if (activeArrows == 0 && arrowsLeft == 0) end_ = true;
}
void Game::render() const
{
	SDL_RenderClear(renderer_);

	// Render background
	textures[BACKGROUND]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	
	if (!end_)
	{
		// Render Game Objects
		if (bow) bow->render();
		for (Arrow* a : arrows)	if (a->isActive()) a->render();
		for (Balloon* b : balloons)	if (b->isActive()) b->render();

		// Render UI
		if (scoreBoard_) scoreBoard_->render();
	}
	else
	{
		// Render Game Over Screen
		textures[GAME_OVER]->render({ (WIN_WIDTH / 2) - 300,
									  (WIN_HEIGHT / 2) + 75,
									  600, 100 });
	}
		
	SDL_RenderPresent(renderer_);
}

void Game::saveState()
{
	std::ofstream stream;
	stream.open(STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open state.txt\n");

	stream << score_ << " " << arrowsLeft << std::endl;
	bow->saveState(stream);
	Uint32 activeArrows = 0;
	for (Arrow* a : arrows)	if (a->isActive()) activeArrows++;
	stream << activeArrows << std::endl;
	for (Arrow* a : arrows)	if (a->isActive()) a->saveState(stream);
	Uint32 activeBalloons = 0;
	for (Balloon* b : balloons)	if (b->isActive()) activeBalloons++;
	stream << activeBalloons << std::endl;
	for (Balloon* b : balloons)	if (b->isActive()) b->saveState(stream);

	stream.close();
}
void Game::loadState()
{
	std::ifstream stream;
	stream.open(STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open state.txt\n");

	stream >> score_ >> arrowsLeft;
	loadEntities();
	bow->loadState(stream);
	
	Uint32 activeArrows = 0;
	stream >> activeArrows;
	for (Uint32 i = 0; i < activeArrows; i++)
	{
		Arrow* a = new Arrow(textures[Game::ARROW],	{ 0, 0 },
							 ARROW_WIDTH, ARROW_HEIGHT, ARROW_SPEED, 0);
		a->loadState(stream);
		arrows.push_back(a);
	}

	Uint32 activeBalloons = 0;
	stream >> activeBalloons;
	for (Uint32 i = 0; i < activeBalloons; i++)
	{
		Balloon* b = new Balloon(this, textures[BALLOONS], { 0, 0 });
		b->loadState(stream);
		balloons.push_back(b);
	}

	stream.close();
}