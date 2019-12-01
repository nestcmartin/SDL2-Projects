#include "Game.h"

Game::Game() :
	bow_(nullptr),
	window_(nullptr),
	renderer_(nullptr),
	scoreBoard_(nullptr),
	end_(false),
	exit_(false),
	changeLevel_(false),
	lastSpawnTime_(0),
	currentLevel_(1)
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
	eventHandlers_.clear();
	balloons_.clear();
	arrows_.clear();
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
		Uint32 score = scoreBoard_->getScore();
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
		int score = (numHits - 1) * (numHits - 1) * POINTS_PER_BALLON;
		scoreBoard_->setScore(scoreBoard_->getScore() + score);

		if (rand() % 100 < 30)
		{
			Reward* r = new Reward(this, textures_[REWARDS], REWARD_WIDTH, REWARD_HEIGHT, 
				{ static_cast<double>(b->getDestRect().x), static_cast<double>(b->getDestRect().y) + BALLOON_HEIGHT },
				{ 0, 1 }, REWARD_SPEED, 0);
			eventHandlers_.push_back(r);
			rewards_.push_back(r);
			addGameObject(r);
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

	if (collision) scoreBoard_->setScore(scoreBoard_->getScore() - (POINTS_PER_BALLON / 2));
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
	auto it = arrows_.insert(arrows_.end(), a);
	a->setArrowIterator(it);
	addGameObject(a);
}

void Game::addBalloon(Balloon* b)
{
	auto it = balloons_.insert(balloons_.end(), b);
	b->setBalloonIterator(it);
	addGameObject(b);
}

void Game::addButterfly(Butterfly* b)
{
	auto it = butterflies_.insert(butterflies_.end(), b);
	b->setButterflyIterator(it);
	addGameObject(b);
}

void Game::addRewardBubble(Reward* r)
{
	auto it = rewards_.insert(rewards_.end(), r);
	r->setRewardIterator(it);
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
			else if (event.key.keysym.sym == SDLK_s)
			{
				saveState();
			}
			else if (event.key.keysym.sym == SDLK_l)
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

	for (GameObject* o : gameObjects_)
	{
		o->update();
	}
	
	if (scoreBoard_) scoreBoard_->update();
	if ((scoreBoard_ && scoreBoard_->getScore() > currentLevel_ * POINTS_PER_LEVEL) || changeLevel_) changeLevel();
	if (scoreBoard_ && scoreBoard_->getArrowsLeft() == 0 && arrows_.empty()) end_ = true;
}

void Game::render() const
{
	SDL_RenderClear(renderer_);

	// Render background
	if (currentLevel_ == 1) textures_[BACKGROUND_1]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	else if (currentLevel_ == 2) textures_[BACKGROUND_2]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	else if (currentLevel_ == 3) textures_[BACKGROUND_3]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	else textures_[BACKGROUND_4]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	
	if (!end_)
	{
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
