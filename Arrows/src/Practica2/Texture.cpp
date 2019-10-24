#include "Texture.h"


Texture::Texture(SDL_Renderer* r) :
	texture(nullptr),
	renderer(r),
	w(0),
	h(0),
	fw(0),
	fh(0),
	numCols(1),
	numRows(1)
{
}

Texture::Texture(SDL_Renderer* r, std::string filename, Uint32 numRows, Uint32 numCols) :
	texture(nullptr),
	renderer(r),
	w(0),
	h(0),
	fw(0),
	fh(0),
	numCols(1),
	numRows(1)
{
	load(filename, numRows, numCols);
};

Texture::~Texture()
{
	freeTexture();
}

void Texture::freeTexture()
{
   SDL_DestroyTexture(texture);
   texture = nullptr;
   w = h = 0;
}

void Texture::load(std::string filename, Uint32 nRows, Uint32 nCols) 
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (!tempSurface) throw FileNotFoundError(SDL_GetError());
	
	freeTexture();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) throw FileNotFoundError(SDL_GetError());

	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;

	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = 0; 
	srcRect.y = 0;
	srcRect.w = w; 
	srcRect.h = h;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, nullptr, flip);
}
