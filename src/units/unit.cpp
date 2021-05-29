#include "unit.hpp"

#include "SDL2/SDL.h"
#include "globals.hpp"
#include "renderer.hpp"

#define VISION 1  // "лучи" зрения юнитов

unsigned int Unit::_unitsCount = 0;

Unit::Unit() : RotateEntity::RotateEntity() { _id = ++_unitsCount; }

void Unit::process()
{
  if (VISION)
  {
    SDL_SetRenderDrawColor(renderer->getRender(), 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer->getRender(), _center->x, _center->y, getFront(), _center->y);
    SDL_SetRenderDrawColor(renderer->getRender(), 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer->getRender(), _center->x, _center->y, getBack(), _center->y);
  }
}

void Unit::process(Unit *next) { Unit::process(); }

void Unit::getDamage(unsigned short int damage)
{
  if (_hp > damage)
    _hp -= damage;
  else
    _hp = 0;
}

int Unit::getBack(void) { return 0; }

int Unit::getFront(void) { return 0; }

unsigned short int Unit::getId(void) { return _id; }

Unit::~Unit() {}
