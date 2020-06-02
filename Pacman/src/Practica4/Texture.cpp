#include <iostream>

#include <SDL_image.h>

#include "Texture.h"

Texture::Texture() :
	texture_(nullptr), 
	renderer_(nullptr), 
	width_(0), 
	height_(0) 
{
}

Texture::Texture(SDL_Renderer* renderer, std::string fileName) :
	texture_(nullptr), 
	width_(0),
	height_(0) 
{
	loadFromImg(renderer, fileName);
}

Texture::Texture(SDL_Renderer* renderer, std::string text, Font* font, const SDL_Color color) :
	texture_(nullptr), 
	width_(0), 
	height_(0) 
{
	loadFromText(renderer, text, font, color);
}

Texture::~Texture() 
{
	close();
}

void Texture::close() 
{
	if (texture_) 
	{
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::loadFromImg(SDL_Renderer* renderer, std::string fileName) 
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface) 
	{
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_) 
		{
			width_ = surface->w;
			height_ = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	else throw "Couldn't load image: " + fileName;
	renderer_ = renderer;
	return texture_;
}

bool Texture::loadFromText(SDL_Renderer* renderer, std::string text, Font* font, const SDL_Color color) 
{
	SDL_Surface* textSurface = font->renderText(text, color);
	if (textSurface) 
	{
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_) 
		{
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else throw "Couldn't create text: " + text;
	renderer_ = renderer;
	return texture_;
}

void Texture::render(int x, int y) const 
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(dest);
}

void Texture::render(const SDL_Rect& dest, const SDL_Rect& clip) const 
{
	if (texture_) 
	{
		SDL_RenderCopy(renderer_, texture_, &clip, &dest);
	}
}

void Texture::render(const SDL_Rect& dest) const 
{
	SDL_Rect clip = { 0, 0, width_, height_ };
	render(dest, clip);
}

void Texture::render(const SDL_Rect& dest, double angle, const SDL_Rect& clip) const 
{
	if (texture_) 
	{
		SDL_RenderCopyEx(renderer_, texture_, &clip, &dest, angle, nullptr, SDL_FLIP_NONE);
	}
}

void Texture::render(const SDL_Rect& dest, double angle) const 
{
	SDL_Rect clip = { 0, 0, width_, height_ };
	render(dest, angle, clip);
}
