#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include <SDL.h>

#include "Font.h"

class Texture 
{
private:
	SDL_Texture* texture_;
	SDL_Renderer* renderer_;

	int width_;
	int height_;

public:
	Texture();
	Texture(SDL_Renderer* renderer, std::string fileName);
	Texture(SDL_Renderer* renderer, std::string text, Font* font, const SDL_Color color);
	virtual ~Texture();

	inline int getWidth() { return width_; }
	inline int getHeight() { return height_; }
	inline bool isReady() { return texture_ != nullptr; }

	bool loadFromImg(SDL_Renderer* renderer, std::string fileName);
	bool loadFromText(SDL_Renderer* renderer, std::string texto, Font* font, SDL_Color color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y).
	void render(int x, int y) const;

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect& dest) const;
	void render(const SDL_Rect& dest, const SDL_Rect& clip) const;

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect& dest, double angle, const SDL_Rect& clip) const;
	void render(const SDL_Rect& dest, double angle) const;
	void close();
};

#endif // !__TEXTURE_H__