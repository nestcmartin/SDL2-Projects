#include <assert.h>

#include <SDL_image.h>

#include "SDLTexturesManager.h"

SDLTexturesManager::SDLTexturesManager() :
	initialized_(false) {
}

SDLTexturesManager::~SDLTexturesManager() 
{
	if (!initialized_) return;

	for (const auto& pair : textures_) 
	{
		if (pair.second) delete pair.second;
	}

	IMG_Quit();
}

bool SDLTexturesManager::init() 
{
	if (initialized_) return false;

	int imgInit_ret = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);
	
	initialized_ = true;
	return true;
}

bool SDLTexturesManager::loadFromImg(int tag, SDL_Renderer* renderer, std::string fileName) 
{
	if (!initialized_) return false;

	Texture* texture = new Texture(renderer, fileName);
	if (texture->isReady()) 
	{
		storeTexture(tag, texture);
		return true;
	}

	return false;
}

bool SDLTexturesManager::loadFromText(int tag, SDL_Renderer* renderer, std::string text, Font* font, SDL_Color color) 
{
	if (!initialized_) return false;

	Texture* texture = new Texture(renderer, text, font, color);
	if (texture->isReady()) 
	{
		storeTexture(tag, texture);
		return true;
	}

	return false;
}

void SDLTexturesManager::storeTexture(int tag, Texture* texture) 
{
	Texture* curr = textures_[tag];
	if (curr != nullptr) delete curr;
	textures_[tag] = texture;
}
