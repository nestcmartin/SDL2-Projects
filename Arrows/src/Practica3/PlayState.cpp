#include "PlayState.h"
#include "SDLApplication.h"

PlayState::PlayState(SDLApplication* a, int code) :
	GameState(a),
	changeLevel_(false),
	lastSpawnTime_(0),
	currentLevel_(0),
	bow_(nullptr),
	scoreBoard_(nullptr),
	leaderBoard_(nullptr)
{
	srand(static_cast<unsigned int>(time(NULL)));
	initScene();
	changeLevel();
}

PlayState::~PlayState()
{
	clearScene();
}



void PlayState::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			app_->toPauseState(app_);
		}
	}

	GameState::handleEvents(event);
}

void PlayState::update()
{
	spawnBallon();

	GameState::update();

	if (scoreBoard_)
	{
		scoreBoard_->update();
		if ((scoreBoard_->getScore() > currentLevel_* POINTS_PER_LEVEL) || changeLevel_) changeLevel();
		if ((scoreBoard_->getArrowsLeft() == 0 && arrows_.empty()) || Butterfly::count == 0) app_->toEndState(app_);
	}

	eraseObjects();
}

void PlayState::render() const
{
	app_->textures["BACKGROUND_" + std::to_string(currentLevel_)]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	GameState::render();

	if (scoreBoard_) scoreBoard_->render();
}



void PlayState::initScene()
{
	bow_ = new Bow(this, app_->textures["BOW"], app_->textures["ARROW"], BOW_WIDTH, BOW_HEIGHT, { 50, WIN_HEIGHT / 2 }, BOW_DIR, BOW_SPEED, 0);
	addEventHandler(bow_);
	addGameObject(bow_);

	scoreBoard_ = new ScoreBoard(app_, app_->textures["ARROW_UI"], app_->textures["DIGITS"]);
	leaderBoard_ = new LeaderBoard();
}

void PlayState::clearScene()
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

void PlayState::eraseObjects()
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

void PlayState::changeLevel()
{
	changeLevel_ = false;
	if (currentLevel_ < NUM_LEVELS)
	{
		currentLevel_++;
		int score = scoreBoard_->getScore();
		clearScene();
		initScene();

		for (int i = 0; i < NUM_BUTTERFLIES_PER_LEVEL * currentLevel_; i++)
		{
			Butterfly* b = new Butterfly(this, app_->textures["BUTTERFLY"], BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, { 0, 0 }, { 0, 0 }, BUTTERFLY_SPEED, 0);
			addButterfly(b);
		}

		scoreBoard_->setScore(score);
	}
}



void PlayState::spawnBallon()
{
	Uint32 elapsedTime = SDL_GetTicks() - lastSpawnTime_;

	if (elapsedTime > SPAWN_TIME)
	{
		Uint32 rndx = rand() % SPAWN_SPACE + SPAWN_LOWER_BOUND;

		Balloon* b = new Balloon(this, app_->textures["BALLOONS"], BALLOON_WIDTH, BALLOON_HEIGHT,
			{ static_cast<double>(rndx), WIN_HEIGHT }, BALLOON_DIR, BALLOON_MIN_SPEED, 0);

		balloons_.push_back(b);
		addGameObject(b);

		lastSpawnTime_ = SDL_GetTicks();
	}
}

void PlayState::shootArrow(Arrow* a)
{
	scoreBoard_->setArrowsLeft(scoreBoard_->getArrowsLeft() - 1);
	addArrow(a);
}

bool PlayState::hitBalloon(Balloon* b)
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
			Reward* r = new Reward(this, app_->textures["REWARDS"], app_->textures["BUBBLE"], REWARD_WIDTH, REWARD_HEIGHT,
				{ static_cast<double>(b->getDestRect().x), static_cast<double>(b->getDestRect().y) + BALLOON_HEIGHT },
				{ 0, 1 }, REWARD_SPEED, 0);
			addRewardBubble(r);
		}
	}
	return collision;
}

bool PlayState::hitButterfly(Butterfly* b)
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

bool PlayState::hitRewardBubble(Reward* b)
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

void PlayState::rewardNextLevel()
{
	changeLevel_ = true;
}

void PlayState::rewardMoreArrows()
{
	scoreBoard_->setArrowsLeft(scoreBoard_->getArrowsLeft() + 2);
}



void PlayState::killArrow(std::list<GameObject*>::iterator it)
{
	arrows_.remove(static_cast<Arrow*>((*it)));
	killGameObject(it);
}

void PlayState::killBalloon(std::list<GameObject*>::iterator it)
{
	balloons_.remove(static_cast<Balloon*>((*it)));
	killGameObject(it);
}

void PlayState::killButterfly(std::list<GameObject*>::iterator it)
{
	butterflies_.remove(static_cast<Butterfly*>((*it)));
	killGameObject(it);
}

void PlayState::killReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator eit)
{
	rewards_.remove(static_cast<Reward*>((*it)));
	eventHandlers_.remove((*eit));
	killGameObject(it);
}

void PlayState::killGameObject(std::list<GameObject*>::iterator it)
{
	erasableObjects_.push_back(it);
}



void PlayState::addArrow(Arrow* a)
{
	arrows_.push_back(a);
	addGameObject(a);
}

void PlayState::addBalloon(Balloon* b)
{
	balloons_.push_back(b);
	addGameObject(b);
}

void PlayState::addButterfly(Butterfly* b)
{
	butterflies_.push_back(b);
	addGameObject(b);
}

void PlayState::addRewardBubble(Reward* r)
{
	rewards_.push_back(r);
	addEventHandler(r);
	addGameObject(r);
}



void PlayState::saveState(int code)
{
	std::cout << "Guardando...\n";

	std::ofstream stream;
	stream.open(std::to_string(code) + STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("No se pudo abrir el fichero de guardado " + std::to_string(code) + STATE_FILE + "\n");

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

	std::cout << "Partida guardada!\n";
}

void PlayState::loadState(int code)
{
	std::cout << "Cargando...\n";

	Arrow::count = 0;
	Balloon::count = 0;
	Butterfly::count = 0;
	Reward::count = 0;

	std::ifstream stream;
	stream.open(std::to_string(code) + STATE_FILE);
	if (!stream.is_open()) throw FileNotFoundError("No se pudo abrir el fichero de guardado " + std::to_string(code) + STATE_FILE + "\n");

	int score;
	int arrowsLeft;
	stream >> currentLevel_ >> score >> arrowsLeft;

	scoreBoard_ = new ScoreBoard(app_, app_->textures["ARROW_UI"], app_->textures["DIGITS"]);
	leaderBoard_ = new LeaderBoard();
	scoreBoard_->setScore(score);
	scoreBoard_->setArrowsLeft(arrowsLeft);

	bow_ = new Bow(this, app_->textures["BOW"], app_->textures["ARROW"], BOW_WIDTH, BOW_HEIGHT, { 50, WIN_HEIGHT / 2 }, BOW_DIR, BOW_SPEED, 0);
	bow_->loadFromFile(stream);
	addEventHandler(bow_);
	addGameObject(bow_);

	int count = 0;

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Arrow* a = new Arrow(this, app_->textures["ARROW"], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		a->loadFromFile(stream);
		addArrow(a);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Balloon* b = new Balloon(this, app_->textures["BALLOONS"], ARROW_WIDTH, ARROW_HEIGHT, { 0, 0 }, ARROW_DIR, ARROW_SPEED, 0);
		b->loadFromFile(stream);
		addBalloon(b);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Butterfly* b = new Butterfly(this, app_->textures["BUTTERFLY"], BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, { 0, 0 }, { 0, 0 }, BUTTERFLY_SPEED, 0);
		b->loadFromFile(stream);
		addButterfly(b);
	}

	stream >> count;
	for (int i = 0; i < count; i++)
	{
		Reward* r = new Reward(this, app_->textures["REWARDS"], app_->textures["BUBBLE"], REWARD_WIDTH, REWARD_HEIGHT, { 0, 0 }, { 0, 0 }, REWARD_SPEED, 0);
		r->loadFromFile(stream);
		addRewardBubble(r);
	}

	stream.close();

	std::cout << "Partida cargada!\n";
}