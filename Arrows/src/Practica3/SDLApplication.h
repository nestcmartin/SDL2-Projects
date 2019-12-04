#ifndef __SDL_APPLICATION_H__
#define __SDL_APPLICATION_H__

#include <map>
#include <time.h>

#include "SDLError.h"
#include "MainMenuState.h"
#include "GameStateMachine.h"

class SDLApplication
{
public:
	static std::map<std::string, Texture*> textures;

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	GameStateMachine* gameStateMachine_;

	bool error_;
	static bool exit_;

public:
	SDLApplication();
	~SDLApplication();

	void run();

	static void closeApplication(SDLApplication* app);

private:
	void handleEvents();
	void update();
	void render() const;

	void loadTextures();
};

#endif // !__SDL_APPLICATION_H__