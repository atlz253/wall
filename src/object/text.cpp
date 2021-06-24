#include "text.hpp"

#include "globals.hpp"

void Text::_updateTexture(void)
{
  SDL_DestroyTexture(_texture);

  if (_text.length())
  {
    _texture = font->getTexture(_text, _size, _color);
    font->getSize(_text, _size, &_geometry->w, &_geometry->h);
  }
  else
  {
    _texture = nullptr;
  }
}

Text::Text(std::string text, FontSize size, SDL_Color color, int x = 0, int y = 0) : Entity::Entity()
{
  _text = text;
  _size = size;
  _color = color;

  _updateTexture();

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
