#include <time.h>
#include <iostream>

#include "SDLGame.h"
#include "SDLFontsManager.h"
#include "SDLAudioManager.h"
#include "SDLTexturesManager.h"
#include "SRandBasedGenerator.h"

std::unique_ptr<SDLGame> SDLGame::instance_;

SDLGame::SDLGame(std::string windowTitle, int width, int height) : 
	windowTitle_(windowTitle), 
	windowWidth_(width), 
	windowHeight_(height)
{
	initSDL();
	initResources();
}

SDLGame::~SDLGame() 
{
	closeResources();
	closeSDL();
}

void SDLGame::initSDL() 
{
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

	// Window
	window_ = SDL_CreateWindow(windowTitle_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Renderer
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
	assert(renderer_ != nullptr);

	int sdlSetDrawColor_ret = SDL_SetRenderDrawColor(renderer_, 0, 100, 100, 255);
	assert(sdlSetDrawColor_ret != -1);

	int sdlRenderClear_ret = SDL_RenderClear(renderer_);
	assert(sdlRenderClear_ret != -1);

	SDL_RenderPresent(renderer_);

	// Cursor
	SDL_ShowCursor(0);
}

void SDLGame::closeSDL() 
{
	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

void SDLGame::initResources() 
{
	randomGenerator_ = new SRandBasedGenerator();
	randomGenerator_->init();

	texturesManager_ = new SDLTexturesManager();
	texturesManager_->init();

	fontsManager_ = new SDLFontsManager();
	fontsManager_->init();

	audioManager_ = new SDLAudioManager();
	audioManager_->init();

	for (auto &image : Resources::images_) 
	{
		texturesManager_->loadFromImg(image.id, renderer_, image.fileName);
	}

	for (auto &font : Resources::fonts_) 
	{
		fontsManager_->loadFont(font.id, font.fileName, font.size);
	}

	for (auto &txtmsg : Resources::messages_) 
	{
		texturesManager_->loadFromText(txtmsg.id, renderer_, txtmsg.msg, *fontsManager_->getFont(txtmsg.fontId), txtmsg.color);
	}

	for (auto &sound : Resources::sounds_) 
	{
		audioManager_->loadSound(sound.id, sound.fileName);
	}

	for (auto &music : Resources::musics_) 
	{
		audioManager_->loadMusic(music.id, music.fileName);
	}

}

void SDLGame::closeResources() 
{
	delete fontsManager_;
	delete texturesManager_;
	delete randomGenerator_;
	delete audioManager_;
}