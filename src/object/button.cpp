#include "button.hpp"

#include "globals.hpp"
#include "text.hpp"

Button::Button(std::string text, int x = 0, int y = 0, SDL_Event *event = nullptr) : Entity(0, 0, x, y)
{
  int textW, textH;

  _event = event;

  _geometry->w = BUTTON_WIDTH;
  _geometry->h = BUTTON_HEIGHT;

  font->getSize(text, FONT_SMALL, &textW, &textH);
  _text = new Text(text, FONT_SMALL, {255, 0, 0, 255}, x + (_geometry->w - textW) / 2, y + (_geometry->h - textH) / 2);
}

void Button::bindEvent(SDL_Event *event) { _event = event; }

void Button::process(void)
{
  SDL_Point *mousePos = events->getMousePosition();
  bool xRange = mousePos->x > _geometry->x &&
                mousePos->x<_geometry->x + BUTTON_WIDTH, yRange = mousePos->y> _geometry->y &&
                mousePos->y < _geometry->y + BUTTON_HEIGHT;

  if (xRange && yRange)
  {
    _text->setColor({255, 0, 0, 255});
    if (_event && events->leftClick()) SDL_PushEvent(_event);
  }
  else
  {
    _text->setColor({0, 0, 0, 255});
  }
}

void Button::render(void) { _text->render(); }
