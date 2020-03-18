#ifndef __SDL_TEXTURES_MANAGER_H__
#define __SDL_TEXTURES_MANAGER_H__

#include <map>
#include "TexturesManager.h"

class SDLTexturesManager : public TexturesManager 
{
private:
	bool initialized_;
	std::map<int, Texture*> textures_;

public:
	SDLTexturesManager();
	virtual ~SDLTexturesManager();

	inline Texture* getTexture(int tag) { return textures_[tag]; }
	
	virtual bool init() override;

	bool loadFromImg(int tag, SDL_Renderer* renderer, std::string fileName) override;
	bool loadFromText(int tag, SDL_Renderer* renderer, std::string text, Font* font, SDL_Color color) override;

private:
	void storeTexture(int tag, Texture* texture);
};

#endif // !__SDL_TEXTURES_MANAGER_H__
