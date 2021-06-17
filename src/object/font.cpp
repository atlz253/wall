#include "font.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "globals.hpp"
#include "print.hpp"

SDL_Texture *renderText(std::string text, int size, SDL_Color color)
{
  TTF_Font *font = TTF_OpenFont("res/font.ttf", size);
  if (!font)
  {
    printError("не удалось открыть шрифт", TTF_GetError());
    return nullptr;
  }

  SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
  if (!surf)
  {
    TTF_CloseFont(font);
    printError("Не удалось преобразовать текст в поверхность", SDL_GetError());
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->getRender(), surf);
  if (!texture)
  {
    printError("Не удалось преобразовать поверхность текста в текстуру", SDL_GetError());
  }

  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  return texture;
}
