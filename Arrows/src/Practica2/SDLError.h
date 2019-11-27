#ifndef __SDL_ERROR_H__
#define __SDL_ERROR_H__

#include "ArrowsError.h"

class SDLError : public ArrowsError
{
public:
	SDLError(const std::string& msg) : ArrowsError(msg) {};
};

#endif // !__SDL_ERROR_H__

