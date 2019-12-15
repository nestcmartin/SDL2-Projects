#include "Font.h"

Font::Font() :
	font_(nullptr)
{
}

Font::~Font() 
{
	close();
}

bool Font::load(std::string filename, int size) 
{
	font_ = TTF_OpenFont(filename.c_str(), size);
	return font_ != nullptr;
}

void Font::close() 
{
	if (font_) 
	{
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

SDL_Surface* Font::renderText(std::string text, SDL_Color color) const 
{
	if (font_) return TTF_RenderText_Blended(font_, text.c_str(), color);
	else return nullptr;
}

int Font::sizeOfText(std::string text, int& w, int& h)
{
	return TTF_SizeText(font_, text.c_str(), &w, &h);
}
