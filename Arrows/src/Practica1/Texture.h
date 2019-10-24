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
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	Uint32 w;
	Uint32 h;
	Uint32 fw; 
	Uint32 fh;
	Uint32 numCols;
	Uint32 numRows;

	void freeTexture();

public:
	Texture(SDL_Renderer* r);
	Texture(SDL_Renderer* r, std::string filename, Uint32 numRows = 1, Uint32 numCols = 1);
	~Texture();	

	inline Uint32 getW() const { return w; };
	inline Uint32 getH() const { return h; };
	inline Uint32 getFW() const { return fw; };
	inline Uint32 getFH() const { return fh; };
	inline Uint32 getNumCols() const { return numCols; };
	inline Uint32 getNumRows() const { return numRows; };
	SDL_Texture* getTexture() const { return texture; };

	void load(std::string filename, Uint32 numRows = 1, Uint32 numCols = 1);
	void render(const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif // !__TEXTURE_H__