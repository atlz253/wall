#include "interface.hpp"

#include <iostream>
#include <queue>

#include "mouse.hpp"

namespace
{
std::queue<void (*)(void)> pendingEvents;
}

namespace button
{
void runPendingEvents(void)
{
  while (!pendingEvents.empty())
  {
    void (*event)(void) = pendingEvents.front();
    pendingEvents.pop();
    if (event)
      event();
  }
}
}

Button::Button(std::string text, Font *font, int w, int h, int x, int y, void (*event)(void)) : Entity(w, h, x, y)
{
  std::cout << "new button" << std::endl;
  int textW, textH;

  this->event = event;
  _selected = false;

  _text = new Text(text, font);
  _text->getSize(&textW, &textH);
  _text->SetPosition(x + (_geometry->w - textW) / 2, y + (_geometry->h - textH) / 2);
}

void Button::process(void)
{
  Point mousePos = mouse::Position();
  bool xRange = mousePos.x > _geometry->x && mousePos.x<_geometry->x + _geometry->w, yRange = mousePos.y> _geometry->y && mousePos.y < _geometry->y + _geometry->h;

  bool hovered = xRange && yRange;

  if (_selected || hovered)
  {
    _text->setColor(255, 0, 0, 255);
    if (event && hovered && mouse::LeftClick())
      pendingEvents.push(event);
  }
  else
  {
    _text->setColor(0, 0, 0, 255);
  }
}

void Button::click(void)
{
  if (event)
    event();
}

void Button::setSelected(bool selected)
{
  _selected = selected;
}

void Button::render(void)
{
  _text->render();
}

Button::~Button()
{
  delete _text;
}
