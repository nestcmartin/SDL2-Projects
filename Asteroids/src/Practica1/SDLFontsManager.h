#ifndef __SDL_FONTS_MANAGER_H__
#define __SDL_FONTS_MANAGER_H__

#include <map>
#include "FontsManager.h"

class SDLFontsManager : public FontsManager 
{
private:
	bool initialized_;
	std::map<int, Font*> fonts_;
	
public:
	SDLFontsManager();
	virtual ~SDLFontsManager();

	virtual bool init();

	virtual Font* getFont(int tag);
	virtual bool loadFont(int tag, std::string fileName, int size);
};

#endif // !__SDL_FONTS_MANAGER_H__