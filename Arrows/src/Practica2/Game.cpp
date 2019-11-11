#include "Game.h"

Game::Game() :
	bow_(nullptr),
	window_(nullptr),
	renderer_(nullptr),
	scoreBoard_(nullptr),
	end_(false),
	exit_(false),
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
		textures_[i] = new Texture(renderer_);
		textures_[i]->load(IMAGE_PATH + textureAttributes[i].filename,
			textureAttributes[i].numRows, textureAttributes[i].numCols);
	}
}

void Game::loadEntities()
{
	bow_ = new Bow(this, textures_[BOW], BOW_WIDTH, BOW_HEIGHT, { 50, WIN_HEIGHT / 2 }, BOW_DIR, BOW_SPEED, 0);
	eventHandlers_.push_back(bow_);
	addGameObject(bow_);

	scoreBoard_ = new ScoreBoard(this, textures_[ARROW_UI], textures_[DIGITS]);
	leaderBoard_ = new LeaderBoard();
}

void Game::clearScene()
{
	delete leaderBoard_; leaderBoard_ = nullptr;
	delete scoreBoard_; scoreBoard_ = nullptr;

	for (ArrowsGameObject* o : gameObjects_)
	{
		delete o; o = nullptr;
	}
}

void Game::clearTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete textures_[i]; textures_[i] = nullptr;
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
		
		Balloon* b = new Balloon(this, textures_[BALLOONS], BALLOON_WIDTH, BALLOON_HEIGHT,
			{ static_cast<double>(rndx), WIN_HEIGHT }, BALLOON_DIR, BALLOON_MIN_SPEED, 0);
		
		balloons_.push_back(b);
		addGameObject(b);

		lastSpawnTime_ = SDL_GetTicks();
	}
}

void Game::shootArrow(Arrow* a)
{
	scoreBoard_->setArrowsLeft(scoreBoard_->getArrowsLeft() - 1);
	arrows_.push_back(a);
	addGameObject(a);
}

bool Game::checkCollision(Balloon* b)
{
	bool collision = false;
	SDL_Rect B = b->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		it++;
	}

	if (collision) scoreBoard_->setScore(scoreBoard_->getScore() + 10);
	return collision;
}

void Game::addGameObject(ArrowsGameObject* o)
{
	o->setIteratorList(gameObjects_.end());
	gameObjects_.push_back(o);
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

	if (end_)
	{
		leaderBoard_->update();
		leaderBoard_->registerPlayerScore(scoreBoard_->getScore());
		leaderBoard_->render();
	}
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

		for (EventHandler* e : eventHandlers_) e->handleEvents(event);
	}
}

void Game::update()
{
	spawnBallon();

	for (ArrowsGameObject* o : gameObjects_)
	{
		o->update();
	}
	
	if (scoreBoard_) scoreBoard_->update();

	// End game
	if (scoreBoard_->getArrowsLeft() == 0)
	{
		end_ = true;
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer_);

	// Render background
	textures_[BACKGROUND]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	
	if (!end_)
	{
		// Render Game Objects
		for (ArrowsGameObject* o : gameObjects_)
		{
			o->render();
		}

		// Render UI
		if (scoreBoard_) scoreBoard_->render();
	}
	else
	{
		// Render Game Over Screen
		textures_[GAME_OVER]->render({ (WIN_WIDTH / 2) - 300,
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

	stream << scoreBoard_->getScore() << " " << scoreBoard_->getArrowsLeft() << std::endl;
	bow_->saveToFile(stream);
	stream << arrows_.size() << std::endl;
	for (Arrow* a : arrows_) a->saveToFile(stream);
	Uint32 activeBalloons = 0;
	for (Balloon* b : balloons_) if (!b->hasBurst()) activeBalloons++;
	stream << activeBalloons << std::endl;
	for (Balloon* b : balloons_) b->saveToFile(stream);

	stream.close();
}
void Game::loadState()
{
	loadEntities();

	std::ifstream stream;
	stream.open(STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open state.txt\n");

	int score;
	int arrowsLeft;
	stream >> score >> arrowsLeft;
	scoreBoard_->setScore(score);
	scoreBoard_->setArrowsLeft(arrowsLeft);

	bow_->loadFromFile(stream);
	
	Uint32 activeArrows = 0;
	stream >> activeArrows;
	for (Uint32 i = 0; i < activeArrows; i++)
	{
		Arrow* a = new Arrow(this, textures_[Game::ARROW], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		a->loadFromFile(stream);
		arrows_.push_back(a);
		addGameObject(a);
	}

	Uint32 activeBalloons = 0;
	stream >> activeBalloons;
	for (Uint32 i = 0; i < activeBalloons; i++)
	{
		Balloon* b = new Balloon(this, textures_[Game::BALLOONS], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		b->loadFromFile(stream);
		balloons_.push_back(b);
		addGameObject(b);
	}

	stream.close();
}