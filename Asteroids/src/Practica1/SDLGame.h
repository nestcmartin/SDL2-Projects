#ifndef __SDL_GAME_H__
#define __SDL_GAME_H__

#include <assert.h>
#include <string>
#include <memory>
#include <SDL.h>

#include "Resources.h"
#include "AudioManager.h"
#include "FontsManager.h"
#include "TexturesManager.h"
#include "RandomNumberGenerator.h"

class SDLGame 
{
protected:
	// Singleton
	static std::unique_ptr<SDLGame> instance_;

	// SDL
	int windowWidth_;
	int windowHeight_;
	std::string windowTitle_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	// Resources Managers
	AudioManager* audioManager_;
	FontsManager* fontsManager_;
	TexturesManager* texturesManager_;

	// Utils
	RandomNumberGenerator* randomGenerator_;

public:
	virtual ~SDLGame();

	SDLGame(SDLGame&) = delete;
	SDLGame& operator=(SDLGame&) = delete;

	inline static SDLGame* init(std::string windowTitle, int width, int height)
	{
		assert(!instance_.get());
		instance_.reset(new SDLGame(windowTitle, width, height));
		return instance_.get();
	}
	inline static SDLGame* instance()
	{
		assert(instance_.get());
		return instance_.get();
	}

	inline int getWindowWidth() const { return windowWidth_; }
	inline int getWindowHeight() const { return windowHeight_; }
	inline SDL_Window* getWindow() const { return window_; }
	inline SDL_Renderer* getRenderer() const { return renderer_; }
	inline AudioManager* getAudioManager() const { return audioManager_; }
	inline FontsManager* getFontManager() const { return fontsManager_; }
	inline TexturesManager* getTextureManager() const { return texturesManager_; }
	inline RandomNumberGenerator* getRandomGenerator() const { return randomGenerator_; }
	inline Uint32 getCurrentTime() { return SDL_GetTicks(); }

private:
	SDLGame(std::string windowTitle_, int width, int height);

	void initSDL();
	void closeSDL();
	void initResources();
	void closeResources();
};

#endif // !__SDL_GAME_H__