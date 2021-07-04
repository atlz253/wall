#include "unit.hpp"

#include "SDL2/SDL.h"
#include "globals.hpp"

#define VISION 0 // "лучи" зрения юнитов

unsigned int Unit::_unitsCount = 0;

Unit::Unit() : RotateEntity::RotateEntity() { _id = ++_unitsCount; }

void Unit::process()
{
  if (VISION)
  {
    SDL_SetRenderDrawColor(glob::renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(glob::renderer, _center->x, _center->y, getFront(), _center->y);
    SDL_SetRenderDrawColor(glob::renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(glob::renderer, _center->x, _center->y, getBack(), _center->y);
  }
}

void Unit::process(Unit *next) { Unit::process(); }

void Unit::setDamage(unsigned short int damage)
{
  if (!_hp)
    return;
  else if (_hp > damage)
    _hp -= damage;
  else
    _hp = 0;
}

int Unit::getBack(void) { return 0; }

int Unit::getFront(void) { return 0; }

Uint16 Unit::getHealth(void) { return _hp; }

Uint32 Unit::getId(void) { return _id; }

Uint16 Unit::getReward(void) { return 0; }

Uint32 Unit::getCount(void) { return _unitsCount; }

void Unit::clearCount(void) { _unitsCount = 0; }

Unit::~Unit() {}
