#ifndef __SDL_MACROS__
#define __SDL_MACROS__

#include <string>
#include <SDL.h>

// Funci�n que realiza un casting autom�tico a enteros de los par�metros de un rect�ngulo
#define RECT(x, y, w, h) { static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) }

// Funci�n que descompone un SDL_Color en sus componentes RRBA
#define COLOREXP(color) color.r, color.g, color.b, color.a

// Funci�n que permite escribir un SDL_Color como n�mero hexadecimal
#define COLOR(num) static_cast<Uint8>((num >> 24) & 0xff), static_cast<Uint8>((num >> 16) & 0xff), static_cast<Uint8>((num >> 8) & 0xff), static_cast<Uint8>(num & 0xff)

// Funci�n que convierte un c�digo de color hexadecimal en un SDL_Color
SDL_Color hex2sdlcolor(std::string input);

#endif // !__SDL_MACROS__
