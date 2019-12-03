#include "Texture.h"


Texture::Texture(SDL_Renderer* r) :
	texture_(nullptr),
	renderer_(r),
	width_(0),
	height_(0),
	framWidth_(0),
	frameHeight_(0),
	numCols_(1),
	numRows_(1)
{
}

Texture::Texture(SDL_Renderer* r, std::string filename, Uint32 numRows, Uint32 numCols) :
	texture_(nullptr),
	renderer_(r),
	width_(0),
	height_(0),
	framWidth_(0),
	frameHeight_(0),
	numCols_(1),
	numRows_(1)
{
	load(filename, numRows, numCols);
};

Texture::~Texture()
{
	freeTexture();
}

void Texture::freeTexture()
{
   SDL_DestroyTexture(texture_);
   texture_ = nullptr;
   width_ = height_ = 0;
}

void Texture::load(std::string filename, Uint32 nRows, Uint32 nCols) 
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (!tempSurface) throw FileNotFoundError("Could not load surface from " + filename);
	
	freeTexture();
	texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
	if (!texture_) throw FileNotFoundError("Could not load texture " + filename);

	numRows_ = nRows;
	numCols_ = nCols;
	width_ = tempSurface->w;
	height_ = tempSurface->h;
	framWidth_ = width_ / numCols_;
	frameHeight_ = height_ / numRows_;

	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = 0; 
	srcRect.y = 0;
	srcRect.w = width_; 
	srcRect.h = height_;

	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, 0, nullptr, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = framWidth_ * col;
	srcRect.y = frameHeight_ * row;
	srcRect.w = framWidth_;
	srcRect.h = frameHeight_;

	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, nullptr, flip);
}
