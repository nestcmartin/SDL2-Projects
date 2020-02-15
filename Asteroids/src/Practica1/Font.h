#ifndef __FONT_H__
#define __FONT_H__

#include <string>
#include <SDL_ttf.h>

class Font 
{
private:
	TTF_Font* font_;

public:
	Font();
	Font(std::string fileName, int size);
	virtual ~Font();

	bool load(std::string fileName, int size);
	void close();

	SDL_Surface* renderText(std::string text, SDL_Color color) const;
};

#endif // !__FONT_H__
