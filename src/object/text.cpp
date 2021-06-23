#include "text.hpp"

#include "globals.hpp"

Text::Text(std::string text, FontSize size, SDL_Color color, int x = 0, int y = 0) : Entity::Entity()
{
  _text = text;
  _size = size;

  _texture = font->getTexture(text, size, color);
  font->getSize(text, size, &_geometry->w, &_geometry->h);

  _geometry->x = x;
  _geometry->y = y;
}

void Text::setColor(SDL_Color color)
{
  SDL_DestroyTexture(_texture);
  _texture = font->getTexture(_text, _size, color);
}

std::string Text::getText(void) { return _text; }

Text::~Text() {}
