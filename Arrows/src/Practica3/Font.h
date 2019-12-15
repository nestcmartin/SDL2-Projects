#ifndef __FONT_H__
#define __FONT_H__

#include <string>
#include <SDL_ttf.h>

class Font
{
public:
	Font();
	virtual ~Font();

	bool load(std::string filename, int size);
	void close();

	SDL_Surface* renderText(std::string text, SDL_Color color) const;

	int sizeOfText(std::string text, int& w, int& h);

private:
	TTF_Font* font_;
};

#endif // !__FONT_H__