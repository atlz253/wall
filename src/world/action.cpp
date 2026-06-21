#include "action.hpp"

#include <iostream>
#include <vector>

#include "base.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "mouse.hpp"

namespace
{
bool previousPointerDown = false;
}

Action::Action()
{
  _leftTeam = new std::queue<Unit *>;
  _rightTeam = new std::queue<Unit *>;
  _deathQueue = new std::queue<Unit *>;

  action = false;

  _leftBase = nullptr;
  _rightBase = nullptr;
}

void Action::_unitsRenderer(void)
{
  std::vector<Unit *> leftUnits;
  std::vector<Unit *> rightUnits;
  std::queue<Unit *> *leftTmp = new std::queue<Unit *>;
  std::queue<Unit *> *rightTmp = new std::queue<Unit *>;
  std::queue<Unit *> *deathTmp = new std::queue<Unit *>;

  while (!_leftTeam->empty())
  {
    leftUnits.push_back(_leftTeam->front());
    _leftTeam->pop();
  }

  while (!_rightTeam->empty())
  {
    rightUnits.push_back(_rightTeam->front());
    _rightTeam->pop();
  }

  size_t leftIndex = 0;
  size_t rightIndex = 0;

  auto isBlockedByFriend = [](Unit *unit, Unit *other)
  {
    if (!unit->getFlip())
      return other->getBack() <= unit->getFront() && other->getBack() > unit->getBack();
    return other->getBack() >= unit->getFront() && other->getBack() < unit->getBack();
  };

  auto isEnemyAhead = [](Unit *unit, Unit *other)
  {
    if (!unit->getFlip())
      return other->getBack() > unit->getBack();
    return other->getBack() < unit->getBack();
  };

  auto isCloserEnemy = [](Unit *unit, Unit *candidate, Unit *current)
  {
    if (!current)
      return true;
    if (!unit->getFlip())
      return candidate->getBack() < current->getBack();
    return candidate->getBack() > current->getBack();
  };

  auto isCloserFriend = [](Unit *unit, Unit *candidate, Unit *current)
  {
    if (!current)
      return true;
    if (!unit->getFlip())
      return candidate->getBack() < current->getBack();
    return candidate->getBack() > current->getBack();
  };

  auto isFriendCloserThanTarget = [](Unit *unit, Unit *friendUnit, Unit *target)
  {
    if (!friendUnit)
      return false;
    if (!target)
      return true;
    if (!unit->getFlip())
      return friendUnit->getBack() < target->getBack();
    return friendUnit->getBack() > target->getBack();
  };

  auto findTarget = [&](Unit *unit, const std::vector<Unit *> &friends, const std::vector<Unit *> &enemies, Base *enemyBase)
  {
    Unit *friendTarget = nullptr;
    for (Unit *other : friends)
    {
      if (other != unit && other->getHealth() && isBlockedByFriend(unit, other) && isCloserFriend(unit, other, friendTarget))
        friendTarget = other;
    }

    Unit *enemyTarget = nullptr;
    for (Unit *other : enemies)
    {
      if (other->getHealth() && isEnemyAhead(unit, other) && isCloserEnemy(unit, other, enemyTarget))
        enemyTarget = other;
    }

    Unit *target = enemyTarget ? enemyTarget : static_cast<Unit *>(enemyBase);
    if (isFriendCloserThanTarget(unit, friendTarget, target))
      return friendTarget;

    return target;
  };

  while (leftIndex < leftUnits.size() || rightIndex < rightUnits.size())
  {
    Base *enemiesBase;
    std::queue<Unit *> *friendsTmp;
    std::vector<Unit *> *enemies;
    std::vector<Unit *> *friends;
    Unit *cur = nullptr;
    bool leftTeamTurn = rightIndex >= rightUnits.size() ||
                        (leftIndex < leftUnits.size() &&
                         leftUnits[leftIndex]->getId() < rightUnits[rightIndex]->getId());

    if (leftTeamTurn)
    {
      cur = leftUnits[leftIndex++];
      friendsTmp = leftTmp;
      enemies = &rightUnits;
      friends = &leftUnits;
      enemiesBase = _rightBase;
    }
    else
    {
      cur = rightUnits[rightIndex++];
      friendsTmp = rightTmp;
      enemies = &leftUnits;
      friends = &rightUnits;
      enemiesBase = _leftBase;
    }

    if (!cur->getHealth())
    {
      friendsTmp = deathTmp;
      enemiesBase->addMoney(cur->getReward());
    }
    else
    {
      cur->process(findTarget(cur, *friends, *enemies, enemiesBase));
    }

    friendsTmp->push(cur);

    cur->render();
  }

  while (!_deathQueue->empty())
  {
    _deathQueue->front()->process(_deathQueue->front());
    _deathQueue->front()->render();
    deathTmp->push(_deathQueue->front());
    _deathQueue->pop();
  }

  delete _leftTeam;
  _leftTeam = leftTmp;

  delete _rightTeam;
  _rightTeam = rightTmp;

  delete _deathQueue;
  _deathQueue = deathTmp;
}

void Action::_baseRenderer(void)
{
  Unit *tmp = nullptr;
  Point pointerPosition = mouse::Position();
  bool pointerDown = mouse::LeftClick();
  bool pointerPressed = pointerDown && !previousPointerDown;
  previousPointerDown = pointerDown;

  if (action)
  {
    _leftBase->process();
    tmp = _leftBase->keyCheck(pointerPressed && _leftBase->contains(pointerPosition));
    if (tmp)
      _leftTeam->push(tmp);
  }
  _leftBase->render();

  if (action)
  {
    _rightBase->process();
    tmp = _rightBase->keyCheck(pointerPressed && _rightBase->contains(pointerPosition));
    if (tmp)
      _rightTeam->push(tmp);
  }
  _rightBase->render();
}

void Action::start(void)
{
  std::cout << "Action: строим укрепточки" << std::endl;

  clear();
  action = true;

  _leftBase = new Base(-96);
  _rightBase = new Base(1088, FLIP_HORIZONTAL);
}

void Action::stop(void)
{
  action = false;
}

bool Action::isActive(void) const
{
  return _leftBase || _rightBase;
}

void Action::renderer(void)
{
  if (_leftBase)
    _baseRenderer();
  _unitsRenderer();
}

void Action::clear(void)
{
  action = false;

  while (!_leftTeam->empty())
  {
    delete _leftTeam->front();
    _leftTeam->pop();
  }

  while (!_rightTeam->empty())
  {
    delete _rightTeam->front();
    _rightTeam->pop();
  }

  while (!_deathQueue->empty())
  {
    delete _deathQueue->front();
    _deathQueue->pop();
  }

  delete _leftBase;
  _leftBase = nullptr;
  delete _rightBase;
  _rightBase = nullptr;
}

Action::~Action() { clear(); }
