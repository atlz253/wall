#include "button.hpp"

#include <iostream>

#include "global.hpp"
#include "text.hpp"
#include "engine.hpp" // TODO: remove
#include "SDL2/SDL_ttf.h"

Button::Button(std::string text, Font *font, int x = 0, int y = 0, void (*event)(void) = nullptr) : Entity(0, 0, x, y)
{
  std::cout << "new button" << std::endl;
  int textW, textH;

  this->event = event;

  _geometry->w = BUTTON_WIDTH;
  _geometry->h = BUTTON_HEIGHT;

  _text = new Text(text, font);
  _text->getSize(&textW, &textH);
  _text->setPosition(x + (_geometry->w - textW) / 2, y + (_geometry->h - textH) / 2);
}

void Button::process(void)
{
  SDL_Point *mousePos = new SDL_Point;
  SDL_GetMouseState(&mousePos->x, &mousePos->y);
  bool xRange = mousePos->x > _geometry->x &&
                mousePos->x<_geometry->x + BUTTON_WIDTH, yRange = mousePos->y> _geometry->y &&
                mousePos->y < _geometry->y + BUTTON_HEIGHT;

  if (xRange && yRange)
  {
    _text->setColor(255, 0, 0, 255);
    // if (_event && events->leftClick()) // FIXME: eventSubSystem depreceated
    if (event && (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)))
      event();
  }
  else
  {
    _text->setColor(0, 0, 0, 255);
  }
}

void Button::render(void)
{
  _text->render();
}

Button::~Button()
{
  delete _text;
}