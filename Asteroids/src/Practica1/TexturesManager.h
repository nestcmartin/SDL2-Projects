#ifndef __TEXTURES_MANAGER_H__
#define __TEXTURES_MANAGER_H__

#include <string>

#include "Font.h"
#include "Texture.h"

class TexturesManager 
{
public:
	TexturesManager();
	virtual ~TexturesManager();

	virtual bool init() = 0;

	virtual Texture* getTexture(int tag) = 0;
	virtual bool loadFromImg(int tag, SDL_Renderer* renderer, std::string fileName) = 0;
	virtual bool loadFromText(int tag, SDL_Renderer* renderer, std::string texto, Font& font, SDL_Color color = { 0, 0, 0, 255 }) = 0;
};

#endif // !__TEXTURES_MANAGER_H__
