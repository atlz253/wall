#include "action.hpp"

#include <iostream>

#include "base.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"

Action::Action(Renderer *renderer)
{
  _listStart = nullptr;
  _listEnd = nullptr;

  printTrace("Action: строим укрепточки");
  _baseLeft = new Base(-96, SDL_FLIP_HORIZONTAL);
  _baseRight = new Base(1088);

  //  _add(new Knight(300));
  //  _add(new Knight(400));
  _add(new Knight(500));
  _add(new Knight(800, SDL_FLIP_HORIZONTAL));
  //  _add(new Knight(1000, SDL_FLIP_HORIZONTAL));
}

void Action::_add(Unit *unit)
{
  if (_listEnd)
  {
    _listEnd->next = new node;
    _listEnd->next->prev = _listEnd;
    _listEnd->next->next = nullptr;
    _listEnd = _listEnd->next;
  }
  else
  {
    _listStart = new node;
    _listStart->prev = nullptr;
    _listStart->next = nullptr;
    _listEnd = _listStart;
  }

  _listEnd->unit = unit;
}

void Action::renderer(void)
{
  node *cur = _listStart;

  _baseLeft->renderer();
  _baseRight->renderer();

  while (cur)
  {
    Unit *curUnit = cur->unit, *prevUnit = nullptr, *nextUnit = nullptr;

    if (cur->prev) prevUnit = cur->prev->unit;
    if (cur->next) prevUnit = cur->next->unit;

    if (prevUnit)
      if (nextUnit && nextUnit->getFront() > prevUnit->getBack())
        curUnit->process(nextUnit);
      else
        curUnit->process(prevUnit);
    else if (nextUnit)
      curUnit->process(nextUnit);
    else if (curUnit->getFlip())
      curUnit->process(_baseLeft);
    else
      curUnit->process(_baseRight);

    cur->unit->renderer();
    cur = cur->next;
  }
}

Action::~Action()
{
  // FIXME: реализовать деструктор
}
