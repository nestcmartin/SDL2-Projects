#ifndef __SDL_GAME_H__
#define __SDL_GAME_H__

#include <string>
#include <memory>
#include <assert.h>

#include <SDL.h>

#include "Resources.h"
#include "AudioManager.h"
#include "FontsManager.h"
#include "TexturesManager.h"

#include "Networking.h"
#include "InputHandler.h"
#include "RandomNumberGenerator.h"

class SDLGame 
{
protected:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	
	Networking* networking_;

	AudioManager* audio_;
	FontsManager* fonts_;
	TexturesManager* textures_;
	RandomNumberGenerator* random_;

	int width_;
	int height_; 
	std::string windowTitle_;

	static std::unique_ptr<SDLGame> instance_;

public:
	virtual ~SDLGame();

	SDLGame(SDLGame&) = delete;
	SDLGame& operator=(SDLGame&) = delete;

	inline static SDLGame* init(std::string windowTitle, int width, int height) 
	{
		assert(instance_.get() == nullptr);
		instance_.reset(new SDLGame(windowTitle, width, height));
		return instance_.get();
	}

	inline static SDLGame* instance() 
	{
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	inline SDL_Window* getWindow() const { return window_; }
	inline SDL_Renderer* getRenderer() const { return renderer_; }
	inline int getWindowWidth() const { return width_; }
	inline int getWindowHeight() const { return height_; }
	inline FontsManager* getFontManager() const { return fonts_; }
	inline TexturesManager* getTextureManager() const { return textures_; }
	inline AudioManager* getAudioManager() const { return audio_; }
	inline RandomNumberGenerator* getRandomGenerator() const { return random_; }
	inline Networking* getNetworking() { return networking_; }
	inline InputHandler* getInputHandler() const { return InputHandler::instance(); }
	inline Uint32 getTime() { return SDL_GetTicks(); }

	inline void toggleFullScreen() 
	{
		int flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(window_, 0);
		else SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
	}

private:
	SDLGame(std::string windowTitle_, int width, int height);

	void initSDL();
	void closeSDL();
	void initResources(); 
	void closeResources();
};

#endif // !__SDL_GAME_H__