#include "button.hpp"

#include "global.hpp"
#include "text.hpp"
#include "engine.hpp" // TODO: remove

Button::Button(std::string text, int x = 0, int y = 0, SDL_Event *event = nullptr) : Entity(0, 0, x, y)
{
  int textW, textH;

  _event = event;

  _geometry->w = BUTTON_WIDTH;
  _geometry->h = BUTTON_HEIGHT;

  engine::font->getSize(text, FONT_SMALL, &textW, &textH);
  _text = new Text(text, FONT_SMALL, {255, 0, 0, 255}, x + (_geometry->w - textW) / 2, y + (_geometry->h - textH) / 2);
}

void Button::bindEvent(SDL_Event *event) { _event = event; }

void Button::process(void)
{
  SDL_Point *mousePos = new SDL_Point;
  SDL_GetMouseState(&mousePos->x, &mousePos->y);
  bool xRange = mousePos->x > _geometry->x &&
                mousePos->x<_geometry->x + BUTTON_WIDTH, yRange = mousePos->y> _geometry->y &&
                mousePos->y < _geometry->y + BUTTON_HEIGHT;

  if (xRange && yRange)
  {
    _text->setColor({255, 0, 0, 255});
    // if (_event && events->leftClick()) // FIXME: eventSubSystem depreceated
    if (_event && (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)))
      SDL_PushEvent(_event);
  }
  else
  {
    _text->setColor({0, 0, 0, 255});
  }
}

void Button::render(void) { _text->render(); }
