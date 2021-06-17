#ifndef FONT_HPP
#define FONT_HPP

#include <string>

typedef struct SDL_Color SDL_Color;
typedef struct SDL_Texture SDL_Texture;

SDL_Texture *renderText(std::string text, int size, SDL_Color color);

#endif // FONT_HPP
