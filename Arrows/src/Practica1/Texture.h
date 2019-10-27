#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "FileNotFoundError.h"

class Texture 
{
private:
	SDL_Texture* texture_;
	SDL_Renderer* renderer_;

	Uint32 width_;
	Uint32 height_;
	Uint32 framWidth_; 
	Uint32 frameHeight_;
	Uint32 numCols_;
	Uint32 numRows_;

	void freeTexture();

public:
	Texture(SDL_Renderer* r);
	Texture(SDL_Renderer* r, std::string filename, Uint32 numRows = 1, Uint32 numCols = 1);
	~Texture();	

	inline Uint32 getWidth() const { return width_; };
	inline Uint32 getHeight() const { return height_; };
	inline Uint32 getFramWidth() const { return framWidth_; };
	inline Uint32 getFrameHeight() const { return frameHeight_; };
	inline Uint32 getNumCols() const { return numCols_; };
	inline Uint32 getNumRows() const { return numRows_; };
	SDL_Texture* getTexture() const { return texture_; };

	void load(std::string filename, Uint32 numRows = 1, Uint32 numCols = 1);
	void render(const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif // !__TEXTURE_H__