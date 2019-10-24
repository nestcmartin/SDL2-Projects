#include "Game.h"

Game::Game() :
	window_(nullptr),
	renderer_(nullptr),
	score_(0),
	arrowsLeft_(NUM_ARROWS),
	lastSpawnTime_(0),
	end_(false),
	exit_(false),
	bow_(nullptr)
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
	bow_ = new Bow(this, textures[BOW], { 50, WIN_HEIGHT / 2 });
	gameObjects_.push_back(bow_);
	scoreBoard_ = new ScoreBoard(this, textures[ARROW_UI], textures[DIGITS]);
}

void Game::clearScene()
{
	for (GameObject* o : gameObjects_)
	{
		delete o; o = nullptr;
	}
	gameObjects_.clear();
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
		Balloon* b = new Balloon(this, textures[BALLOONS], { static_cast<double>(rndx), WIN_HEIGHT });
		gameObjects_.push_back(b);
		balloons_.push_back(b);
		lastSpawnTime_ = SDL_GetTicks();
	}
}
void Game::shootArrow(Arrow* a)
{
	gameObjects_.push_back(a);
	arrows_.push_back(a);
	arrowsLeft_--;
}
bool Game::checkCollision(Balloon* b)
{
	bool collision = false;
	SDL_Rect B = b->getRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
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
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) exit_ = true;
			if (event.key.keysym.sym == SDLK_s) saveState();
			if (event.key.keysym.sym == SDLK_l)	loadState();
		}

		if (bow_) bow_->handleEvents(event);
	}
}
void Game::update()
{
	spawnBallon();
	for (GameObject* o : gameObjects_) if (o->isActive()) o->update();
	if (scoreBoard_) scoreBoard_->update();

	// End game
	Uint32 activeArrows = 0;
	for (Arrow* a : arrows_) if (a->isActive()) activeArrows++;
	if (activeArrows == 0 && arrowsLeft_ == 0) end_ = true;
}
void Game::render() const
{
	SDL_RenderClear(renderer_);

	// Render background
	textures[BACKGROUND]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	
	if (!end_)
	{
		for (GameObject* o : gameObjects_) if (o->isActive()) o->render();
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

	stream << score_ << " " << arrowsLeft_ << std::endl;
	bow_->saveState(stream);
	Uint32 activeArrows = 0;
	for (Arrow* a : arrows_) if (a->isActive()) activeArrows++;
	stream << std::endl << activeArrows << std::endl;
	for (Arrow* a : arrows_) if (a->isActive()) a->saveState(stream);
	Uint32 activeBalloons = 0;
	for (Balloon* b : balloons_) if (b->isActive()) activeBalloons++;
	stream << std::endl << activeBalloons << std::endl;
	for (Balloon* b : balloons_) if (b->isActive()) b->saveState(stream);

	stream.close();
}
void Game::loadState()
{
	clearScene();
	loadEntities();

	std::ifstream stream;
	stream.open(STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open state.txt\n");

	stream >> score_ >> arrowsLeft_;
	bow_->loadState(stream);

	Uint32 activeArrows = 0;
	stream >> activeArrows;
	for (Uint32 i = 0; i < activeArrows; i++)
	{
		Arrow* a = new Arrow(this, textures[Game::ARROW], { 0, 0 }, 0, 0.0);
		gameObjects_.push_back(a);
		arrows_.push_back(a);
		a->loadState(stream);
	}

	Uint32 activeBalloons = 0;
	stream >> activeBalloons;
	for (Uint32 i = 0; i < activeBalloons; i++)
	{
		Balloon* b = new Balloon(this, textures[BALLOONS], { 0, 0 });
		gameObjects_.push_back(b);
		balloons_.push_back(b);
		b->loadState(stream);
	}

	stream.close();
}