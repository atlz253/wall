#include "unit.hpp"

Unit::Unit() : RotateEntity::RotateEntity() {}

void Unit::process(Unit *next) {}

void Unit::getDamage(unsigned short int damage)
{
  if (_hp > damage)
    _hp -= damage;
  else
    _hp = 0;
}

int Unit::getBack(void) { return 0; }

int Unit::getFront(void) { return 0; }

Unit::~Unit() {}
