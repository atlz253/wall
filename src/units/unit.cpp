#include "unit.hpp"

#include "globals.hpp"

unsigned int Unit::_unitsCount = 0;

Unit::Unit() : RotateEntity::RotateEntity() { _id = ++_unitsCount; }

void Unit::process()
{
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

uint16_t Unit::getHealth(void) { return _hp; }

uint32_t Unit::getId(void) { return _id; }

uint16_t Unit::getReward(void) { return 0; }

uint32_t Unit::getCount(void) { return _unitsCount; }

void Unit::clearCount(void) { _unitsCount = 0; }

Unit::~Unit() {}
