#ifndef __SDL_APPLICATION_H__
#define __SDL_APPLICATION_H__

#include <map>

#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "GameStateMachine.h"

class SDLApplication
{
private:
	bool error_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	
	static bool exit_;
	static GameStateMachine* gameStateMachine_;

	std::map<std::string, Texture*> textures_;
	std::map<std::string, Font*> fonts_;

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

	inline SDL_Renderer* getRenderer() { return renderer_; }
	inline Texture* getTexture(std::string s) { return textures_[s]; }
	inline Font* getFont(std::string s) { return fonts_[s]; }

private:
	void handleEvents();
	void update();
	void render() const;

	void loadTextures();
	void loadFonts();
};

#endif // !__SDL_APPLICATION_H__