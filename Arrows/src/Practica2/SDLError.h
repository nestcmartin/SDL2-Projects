#ifndef __SDL_ERROR_H__
#define __SDL_ERROR_H__

#include <stdexcept>

class SDLError : public std::logic_error
{
public:
	SDLError(const std::string& msg) : logic_error(msg) {};
};

#endif // !__SDL_ERROR_H__

