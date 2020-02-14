#pragma once

#include <SDL.h>
#include "Font.h"
#include <string>

using namespace std;

class Texture {
public:
	Texture();
	Texture(SDL_Renderer *renderer, string fileName);
	Texture(SDL_Renderer *renderer, string text, Font &font,
			const SDL_Color color);
	virtual ~Texture();

	inline int getWidth() {
		return width_;
	}

	inline int getHeight() {
		return height_;
	}

	inline bool isReady() {
		return texture_ != nullptr;
	}

	// load from image or text, in both cases we should provide a rendered
	bool loadFromImg(SDL_Renderer *renderer, string fileName);
	bool loadFromText(SDL_Renderer *renderer, string texto, Font &font,
			SDL_Color color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y). We either provide
	// a renderer or use the one used at construction
	void render(SDL_Renderer *renderer, int x, int y) const;
	inline void render(int x, int y) const {
		render(renderer_, x, y);
	}

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest). We either provide
	// a renderer or use the one used at construction
	void render(SDL_Renderer *renderer, SDL_Rect const &dest, SDL_Rect *clip =
			nullptr) const;
	inline void render(SDL_Rect const &dest, SDL_Rect *clip = nullptr) const {
		render(renderer_, dest, clip);
	}

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest). We either provide
	// a renderer or use the one used at construction
	void render(SDL_Renderer *renderer, SDL_Rect const &dest, double angle,
			SDL_Rect *clip = nullptr) const;
	void render(SDL_Rect const &dest, double angle,
			SDL_Rect *clip = nullptr) const {
		render(renderer_, dest, angle, clip);
	}

	void close();

private:
	SDL_Texture *texture_;
	SDL_Renderer *renderer_;
	int width_;
	int height_;
};
