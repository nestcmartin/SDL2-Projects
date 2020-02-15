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
	Texture(SDL_Renderer* renderer, std::string text, Font& font, const SDL_Color color);
	virtual ~Texture();

	inline int getWidth() { return width_; }
	inline int getHeight() { return height_; }
	inline bool isReady() { return texture_ != nullptr; }

	// Carga una textura desde un archivo de imagen
	bool loadFromImg(SDL_Renderer* renderer, std::string fileName);
	// Carga una textura a partir de un texto y una fuente
	bool loadFromText(SDL_Renderer* renderer, std::string texto, Font& font, SDL_Color color = { 0, 0, 0, 255 });

	// Renderiza una textura completa en la posición x, y
	// Si no se proporciona renderer se utiliza el proporcionado en la constructora
	void render(SDL_Renderer* renderer, int x, int y) const;
	inline void render(int x, int y) const { render(renderer_, x, y); }

	// Renderiza una parte de una texura (rectángulo fuente) en un rectángulo destino
	// Si no se proporciona un rectángulo fuente se renderiza toda la textura escalada al rectángulo destino
	// Si no se proporciona renderer se utiliza el proporcionado en la constructora
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, SDL_Rect* clip = nullptr) const;
	inline void render(SDL_Rect const& dest, SDL_Rect* clip = nullptr) const { render(renderer_, dest, clip); }

	// Renderiza una parte de una texura (rectángulo fuente) en un rectángulo destino con rotación
	// Si no se proporciona un rectángulo fuente se renderiza toda la textura escalada al rectángulo destino
	// Si no se proporciona renderer se utiliza el proporcionado en la constructora
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, double angle, SDL_Rect* clip = nullptr) const;
	void render(SDL_Rect const& dest, double angle, SDL_Rect* clip = nullptr) const { render(renderer_, dest, angle, clip); }

	void close();
};

#endif // !__TEXTURE_H__