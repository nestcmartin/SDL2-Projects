#include "Game.h"

Game::Game() :
	bow_(nullptr),
	window_(nullptr),
	renderer_(nullptr),
	scoreBoard_(nullptr),
	exit_(false),
	changeLevel_(false),
	lastSpawnTime_(0),
	currentLevel_(1),
	currentState_(MENU_STATE)
{
	srand(static_cast<unsigned int>(time(NULL)));

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

	for (int i = 0; i < NUM_BUTTERFLIES_PER_LEVEL * currentLevel_; i++)
	{
		Butterfly* b = new Butterfly(this, textures_[BUTTERFLY], BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, { 0, 0 }, { 0, 0 }, BUTTERFLY_SPEED, 0);
		butterflies_.push_back(b);
		addGameObject(b);
	}

	scoreBoard_ = new ScoreBoard(this, textures_[ARROW_UI], textures_[DIGITS]);
	leaderBoard_ = new LeaderBoard();
}

void Game::clearScene()
{
	delete leaderBoard_; leaderBoard_ = nullptr;
	delete scoreBoard_; scoreBoard_ = nullptr;

	for (GameObject* o : gameObjects_)
	{
		delete o; o = nullptr;
	}
	gameObjects_.clear();
	arrows_.clear();
	balloons_.clear();
	butterflies_.clear();
	rewards_.clear();
	eventHandlers_.clear();
	erasableObjects_.clear();
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

void Game::changeLevel()
{
	changeLevel_ = false;
	if (currentLevel_ < NUM_LEVELS)
	{
		currentLevel_++;
		int score = scoreBoard_->getScore();
		clearScene();
		loadEntities();
		scoreBoard_->setScore(score);
	}
}

bool Game::hitBalloon(Balloon* b)
{
	bool collision = false;
	SDL_Rect B = b->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		if (!collision) it++;
	}

	if (collision)
	{
		(*it)->addHit();
		Uint32 numHits = (*it)->getNumHits();
		int score = scoreBoard_->getScore() + (numHits - 1) * (numHits - 1) * POINTS_PER_BALLON;
		if (score > 999) score = 999;
		scoreBoard_->setScore(score);

		if (rand() % 100 < 30)
		{
			Reward* r = new Reward(this, textures_[REWARDS], REWARD_WIDTH, REWARD_HEIGHT,
				{ static_cast<double>(b->getDestRect().x), static_cast<double>(b->getDestRect().y) + BALLOON_HEIGHT },
				{ 0, 1 }, REWARD_SPEED, 0);
			addRewardBubble(r);
		}
	}
	return collision;
}

bool Game::hitButterfly(Butterfly* b)
{
	bool collision = false;
	SDL_Rect B = b->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		if (!collision) it++;
	}

	if (collision)
	{
		int score = scoreBoard_->getScore() - (POINTS_PER_BALLON / 2);
		if (score < 0) score = 0;
		scoreBoard_->setScore(score);
	}
	return collision;
}

bool Game::hitRewardBubble(Reward* b)
{
	bool collision = false;
	SDL_Rect B = b->getCollisionRect();

	auto it = arrows_.begin();
	while (it != arrows_.end() && !collision)
	{
		SDL_Rect A = (*it)->getCollisionRect();
		collision = SDL_HasIntersection(&A, &B);
		if (!collision) it++;
	}

	return collision;
}


void Game::addArrow(Arrow* a)
{
	arrows_.push_back(a);
	addGameObject(a);
}

void Game::addBalloon(Balloon* b)
{
	balloons_.push_back(b);
	addGameObject(b);
}

void Game::addButterfly(Butterfly* b)
{
	butterflies_.push_back(b);
	addGameObject(b);
}

void Game::addRewardBubble(Reward* r)
{
	rewards_.push_back(r);
	addEventHandler(r);
	addGameObject(r);
}

void Game::addEventHandler(EventHandler* e)
{
	auto it = eventHandlers_.insert(eventHandlers_.end(), e);
	e->setEventHandlerIterator(it);
}

void Game::addGameObject(ArrowsGameObject* o)
{
	auto it = gameObjects_.insert(gameObjects_.end(), o);
	o->setIteratorList(it);
}


void Game::killArrow(std::list<GameObject*>::iterator it)
{
	arrows_.remove(static_cast<Arrow*>((*it)));
	killGameObject(it);
}

void Game::killBalloon(std::list<GameObject*>::iterator it)
{
	balloons_.remove(static_cast<Balloon*>((*it)));
	killGameObject(it);
}

void Game::killButterfly(std::list<GameObject*>::iterator it)
{
	butterflies_.remove(static_cast<Butterfly*>((*it)));
	killGameObject(it);
}

void Game::killReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator eit)
{
	rewards_.remove(static_cast<Reward*>((*it)));
	eventHandlers_.remove((*eit));
	killGameObject(it);
}

void Game::killGameObject(std::list<GameObject*>::iterator it)
{
	erasableObjects_.push_back(it);
}


void Game::rewardNextLevel()
{
	changeLevel_ = true;
}

void Game::rewardMoreArrows()
{
	scoreBoard_->setArrowsLeft(scoreBoard_->getArrowsLeft() + 2);
}


void Game::run()
{
	while (!exit_ && currentState_ != END_STATE)
	{
		Uint32 startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}

	if (currentState_ == END_STATE)
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
			else if (event.key.keysym.sym == SDLK_s)
			{
				if (currentState_ == PLAY_STATE)
					saveState();
			}
			else if (event.key.keysym.sym == SDLK_l)
			{
				if (currentState_ == MENU_STATE)
				{
					clearScene();
					loadState();
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (currentState_ == MENU_STATE)
				{
					currentState_ = PLAY_STATE;
				}
			}
			// LOS HACKS
			else if (event.key.keysym.sym == SDLK_n)
			{
				if (currentState_ == PLAY_STATE)
					rewardNextLevel();
			}
		}

		if (currentState_ == PLAY_STATE)
			for (EventHandler* e : eventHandlers_) e->handleEvents(event);
	}
}

void Game::update()
{
	if (currentState_ == PLAY_STATE)
	{
		spawnBallon();

		for (GameObject* o : gameObjects_)
		{
			o->update();
		}

		if (scoreBoard_)
		{
			scoreBoard_->update();
			if ((scoreBoard_->getScore() > currentLevel_* POINTS_PER_LEVEL) || changeLevel_) changeLevel();
			if ((scoreBoard_->getArrowsLeft() == 0 && arrows_.empty()) || Butterfly::count == 0) currentState_ = END_STATE;
		}

		eraseObjects();
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer_);

	if (currentState_ == MENU_STATE)
	{
		// Render background
		textures_[BACKGROUND_SPRING]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
		textures_[MENU]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	}
	else if (currentState_ == PLAY_STATE)
	{
		// Render background
		textures_[FIRST_BG_TEXTURE + currentLevel_]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

		// Render Game Objects
		for (GameObject* o : gameObjects_)
		{
			o->render();
		}

		// Render UI
		if (scoreBoard_) scoreBoard_->render();
	}
	else
	{
		// Render background
		textures_[BACKGROUND_AUTUMN]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

		// Render Game Over Screen
		textures_[GAME_OVER]->render({ (WIN_WIDTH / 2) - 300,
									  (WIN_HEIGHT / 2) + 75,
									  600, 100 });
	}

	SDL_RenderPresent(renderer_);
}

void Game::saveState()
{
	int code;
	std::cout << "Introduce c�digo num�rico de guardado: "; std::cin >> code;

	std::ofstream stream;
	stream.open(std::to_string(code) + STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn�t open state.txt\n");

	stream << currentLevel_ << " " << scoreBoard_->getScore() << " " << scoreBoard_->getArrowsLeft() << std::endl;
	bow_->saveToFile(stream); stream << std::endl;
	stream << Arrow::count << std::endl;
	for (Arrow* a : arrows_) { a->saveToFile(stream); stream << std::endl; }
	stream << Balloon::count << std::endl;
	for (Balloon* b : balloons_) { if (!b->hasBurst()) { b->saveToFile(stream); stream << std::endl; } }
	stream << Butterfly::count << std::endl;
	for (Butterfly* b : butterflies_) { b->saveToFile(stream); stream << std::endl; }
	stream << Reward::count << std::endl;
	for (Reward* r : rewards_) { r->saveToFile(stream); stream << std::endl; }

	stream.close();
}

void Game::loadState()
{
	int code;
	std::cout << "Introduce c�digo de archivo de guardado: "; std::cin >> code;

	currentState_ = PLAY_STATE;

	Arrow::count = 0;
	Balloon::count = 0;
	Butterfly::count = 0;
	Reward::count = 0;

	std::ifstream stream;
	stream.open(std::to_string(code) + STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn�t open state.txt\n");

	int score;
	int arrowsLeft;
	stream >> currentLevel_ >> score >> arrowsLeft;

	scoreBoard_ = new ScoreBoard(this, textures_[ARROW_UI], textures_[DIGITS]);
	leaderBoard_ = new LeaderBoard();
	scoreBoard_->setScore(score);
	scoreBoard_->setArrowsLeft(arrowsLeft);

	bow_ = new Bow(this, textures_[BOW], BOW_WIDTH, BOW_HEIGHT, { 50, WIN_HEIGHT / 2 }, BOW_DIR, BOW_SPEED, 0);
	bow_->loadFromFile(stream);
	eventHandlers_.push_back(bow_);
	addGameObject(bow_);

	int count = 0;

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Arrow* a = new Arrow(this, textures_[Game::ARROW], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		a->loadFromFile(stream);
		addArrow(a);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Balloon* b = new Balloon(this, textures_[Game::BALLOONS], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		b->loadFromFile(stream);
		addBalloon(b);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Butterfly* b = new Butterfly(this, textures_[Game::BUTTERFLY], BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, { 0, 0 }, { 0, 0 }, BUTTERFLY_SPEED, 0);
		b->loadFromFile(stream);
		addButterfly(b);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Reward* r = new Reward(this, textures_[Game::REWARDS], REWARD_WIDTH, REWARD_HEIGHT, { 0, 0 }, { 0, 0 }, REWARD_SPEED, 0);
		r->loadFromFile(stream);
		addRewardBubble(r);
	}

	stream.close();
}

void Game::eraseObjects()
{
	auto it = erasableObjects_.begin();
	while (it != erasableObjects_.end())
	{
		delete (**it); (**it) = nullptr;
		gameObjects_.erase(*it);
		it++;
	}
	erasableObjects_.clear();
}