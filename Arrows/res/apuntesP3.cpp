// Tiene la maquina de estados
class Game{ // Se puede llamar SDL_App
	private:
		SDL_Window* window_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		bool error_ = false;
		GameStateMachine* stateMachine_;
		bool exit_ = false;
		Texture* textures_[NUM_TEXTURES];

}

Game::Game()
{
	// SDL
	window_ = SDL_CreateWindow(...);
	renderer_ = SDL_CreateRenderer(...);
	// textures
	...
	// State Machine
	stateMachine_ = new GameStateMachine();
	stateMachine_->pushState(new MainMenuState(this));
}

Game::~Game
{
	delete stateMachine_;
	// borrado de texturas
	...
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

// ---------------------------------------

class GameState
{
protected:
	list<GameObject*> stage_;
	list<EventHandler*> eventHandler_;
	Game* app;

	GameState(Game* g) : app(g) {} // Clase abstracta
}

// ----------------------------------------------

class StateMachine
{
	// tiene una pila con los estados
	// Main Menu State
	// Play State
	// Pause State
	// cada estado tiene sus punteros a objetos
private:
	stack<GameState*> states_;
public:
	// Decision de diseño
	GameStateMachine::~GameStateMachine()
	{
		while (!states_.empty())
			popState();
	}

	GameState* GameStateMachine::currentState() const
	{
		if (!states_.empty()) return states.top();
		else return nullptr;
	}

	void GameStateMachine::pushState(GameState* s)
	{
		states_.push(s);
	}

	void GameStateMachine::changeState(GameState* s)
	{
		popState();
		pushState(s);
	}
	void GameStateMachine::popState()
	{
		if(!states_.empty())
		{
			delete states_.top();
			states_.pop();
		}
	}
}

// ----------------------------------------------

class PlayState: public GameState{
private:
	int points_;
	list <Arrow*> arrows_;
	list<GameObject*> objectsToErase_;

void PlayState::update()
{
	for(auto itOb:objectsToErase_)
	{
		delete*itOb
		objects.erase()
	}
	objectsToErase_.clear();
	...
	if(...)levelPassed_ = true;
	if(levelPassed_)
	{
		if(levele == NUM_LEVELS) exit = true;
		else
		{
			levelPassed_ = false;
			level++;
			loadNextLevel();
		}
	}
}

void PlayState::handleEvent(SDL_Event& event)
{
	if(event.type ...  SDL_p)
		app->getStateMachine()->pushState(new PauseState(game));
	else GameState::handleEvent(event);
}
	
}

// Bool handled_ para que cuando handleEvent() de GameState haga el bucle
// si recoge un evento pone handled a true

void GameState::handleEvent(SDL_Event& event)
{
	bool handled;
	auto it = eventHandlers.begin();
	while(!handled_ && it!=eventHandlers.end())
	{
		if((*it)->handleEvent(event)) handled = true;
		else ++it;
	}
}

// ----------------------------------------------

// metodo action y cada objeto tiene su propio action (como en rewards)
// hace buena estructura, pero implica mucho codigo, por constructoras repetidas etc
// pero ahora podemos hacer CALLBACKS

using CallBackOnClick = void (Game* g);

class PauseState: public GameState
{
	PauseState::PauseState(...) : GameState(...)
	{
		stage.push_back(new MenuButton(...,funcion a invocar))
		// funcion a invocar: resume, back to menu...
	}
}

// ----------------------------------------------

class MenuButton: public SDLGameObject
{
protected:
	Game* game;
	Texture* texture;
	int x, y;
	int w, h;
	CallBackOnClick* cbOnClick_;

bool MenuButton::handleEvent(SDL_Event& e)
{
	bool handled = false;
	if(e.type == SDL_MOUSEBUTTONUP && e.button.button == ...)
		{
			SDL_Point p = {e.button.x, e.button.y};
			SDL_Rect r = {x,y,w,h};
			if(SDL_PointInRect(&p,&r) == SDL_TRUE)
			{
				cbOnClick_(->game);
				handled = true;
			}
		}
	return handled;
}	
}

// ----------------------------------------------

static void resume(Game* g)
{
	app->getStateMachine()->popState();
}

// ----------------------------------------------

void Game::run()
{
	while(!exit)
	{
		handleEvents(); //EVENTSSS
		stateMachine_->currentState()->update();
		render();
		...
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	stateMachine_->currentState()->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event) && !exit)
	{
		stateMachine_->currentState()->handleEvent(event);
		if(event.tyoe == SDL_QUIT)
			exit = true;
	}
}

// ----------------------------------------------

PauseState(Game* game): GameState(g)
{
	uint numButtons = 3;
	uint buttonH = ...;
	uint buttonW = ...;
	// CallbackOnClick* cbResume = [](Game* game){g->getStateMachine...}
	stage.push_back(new MenuButton(g, g->getTexture{ResumeButtonText},...))
	...
}
static void resume(Game* game);
static void backToMenu(Game* game);
static void exitGame(Game* game);
// static CallBackOnClick resume;
// static CallBackOnClick backToMenu;
// static CallBackOnClick exitGame;

// ----------------------------------------------

// Mantener el menu principal en la pila siempre es lo ideal, no crear uno cada vez

// Viene bien empezar de cero con la mauqina de estados, cambiando de estado con teclas
// sin nada de "juego"

// El "envoltorio", que seria la maquina de estados -> TAG#

GAMEOBJECT
	|
SDLGAMEOBJECT		EVENTHANDLER
	|		|		|		 |
ARROWSGO	MENUBUTTON
|	|	|					 |
		BOW		--------------

// ----------------------------------------------
