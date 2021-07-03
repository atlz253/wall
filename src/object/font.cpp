#include "font.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "globals.hpp"
#include "print.hpp"
#include "window.hpp"

TTF_Font *Font::_getFont(FontSize size)
{
  switch (size)
  {
    case FONT_HIGH:
      return _fontHigh;
    case FONT_MEDIUM:
      return _fontMedium;
    case FONT_SMALL:
      return _fontLow;
  }

  return nullptr;
}

Font::Font() { printTrace("Инициализация шрифтов"); }

void Font::open(std::string path)
{
  _fontHigh = TTF_OpenFont(path.c_str(), FONT_HIGH);
  _fontMedium = TTF_OpenFont(path.c_str(), FONT_MEDIUM);
  _fontLow = TTF_OpenFont(path.c_str(), FONT_SMALL);

  if (!_fontHigh || !_fontMedium || !_fontLow) printError("не удалось открыть шрифт", TTF_GetError());
}

SDL_Texture *Font::getTexture(std::string text, FontSize size, SDL_Color color)
{
  TTF_Font *font = _getFont(size);

  SDL_Surface *surf = TTF_RenderUTF8_Blended(font, text.c_str(), color);
  if (!surf)
  {
    printError("Не удалось преобразовать текст в поверхность", TTF_GetError());
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
  if (!texture)
  {
    printError("Не удалось преобразовать поверхность текста в текстуру", SDL_GetError());
    return nullptr;
  }

  SDL_FreeSurface(surf);

  return texture;
}

void Font::getSize(std::string text, FontSize size, int *w, int *h)
{
  TTF_SizeUTF8(_getFont(size), text.c_str(), w, h);
}

Font::~Font()
{
  TTF_CloseFont(_fontHigh);
  TTF_CloseFont(_fontMedium);
  TTF_CloseFont(_fontLow);
}
