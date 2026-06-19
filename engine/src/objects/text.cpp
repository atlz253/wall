#include "interface.hpp"

#include <iostream>

#include "global.hpp"
#include "SDL_ttf.h"

namespace font
{
  Font *open(std::string path, int size)
  {
    Font *font = TTF_OpenFont(path.c_str(), size);

    if (!font)
      std::cout << "could not open font" << TTF_GetError() << std::endl;

    return font;
  }

  void close(Font *font)
  {
    TTF_CloseFont(font);
  }
}

void Text::updateTexture(void)
{
  if (_texture)
    SDL_DestroyTexture(_texture);

  if (!text.length())
    return;

  SDL_Surface *surf = TTF_RenderUTF8_Blended(font, text.c_str(), {color->r, color->g, color->b, color->a});
  if (!surf)
  {
    std::cout << "Failed to convert text to surface" << TTF_GetError() << std::endl;
    return;
  }

  _texture = SDL_CreateTextureFromSurface(global::renderer, surf);
  SDL_FreeSurface(surf);
  if (!_texture)
  {
    std::cout << "Failed to convert text surface to texture" << SDL_GetError() << std::endl;
    return;
  }

  int w, h;
  if (TTF_SizeUTF8(font, text.c_str(), &w, &h))
  {
    std::cout << "Failed to get text size: " << TTF_GetError() << std::endl;
    return;
  }

  _geometry->w = w;
  _geometry->h = h;
}

Text::Text(std::string text, Font *font, int x, int y) : Entity()
{
  this->font = font;
  this->text = text;

  color = new Color;
  setColor(255, 255, 255, 255);

  _geometry->x = x;
  _geometry->y = y;
}

void Text::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
  Color *c = this->color;

  if (c->r == red && c->g == green && c->b == blue && c->a == alpha)
    return;

  *this->color = {red, green, blue, alpha};
  updateTexture();
}

int Text::getWidth(void) { return _geometry->w; }

std::string Text::getText(void) { return text; }

void Text::getSize(int *w, int *h)
{
  TTF_SizeUTF8(font, text.c_str(), w, h);
}

Text::~Text()
{
  delete color;
}
