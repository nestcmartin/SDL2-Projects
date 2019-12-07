#ifndef __SDL_APPLICATION_H__
#define __SDL_APPLICATION_H__

#include <map>
#include <time.h>

#include "SDLError.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "GameStateMachine.h"

class SDLApplication
{
public:
	static std::map<std::string, Texture*> textures;

private:
	bool error_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	
	static bool exit_;
	static GameStateMachine* gameStateMachine_;

public:
	SDLApplication();
	~SDLApplication();

	void run();

	static void toMenuState(SDLApplication* app);
	static void toPlayState(SDLApplication* app);
	static void toPauseState(SDLApplication* app);
	static void toEndState(SDLApplication* app);
	static void closeApplication(SDLApplication* app);
	static void resumeApplication(SDLApplication* app);
	static void savePlayState(SDLApplication* app);
	static void loadPlayState(SDLApplication* app);

private:
	void handleEvents();
	void update();
	void render() const;

	void loadTextures();
};

#endif // !__SDL_APPLICATION_H__