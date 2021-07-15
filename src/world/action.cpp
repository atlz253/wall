#include "action.hpp"

#include <iostream>

#include "base.hpp"
#include "globals.hpp"
#include "knight.hpp"

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
  std::queue<Unit *> *leftTmp = new std::queue<Unit *>;
  std::queue<Unit *> *rightTmp = new std::queue<Unit *>;
  std::queue<Unit *> *deathTmp = new std::queue<Unit *>;

  while (!_leftTeam->empty() || !_rightTeam->empty())
  {
    Base *enemiesBase;
    std::queue<Unit *> *friends, *friendsTmp, *enemies, *enemiesTmp;
    bool leftTeamFilled = !_leftTeam->empty(), rightTeamFilled = !_rightTeam->empty();
    Unit *cur = nullptr, *leftFront = _leftTeam->front(), *rightFront = _rightTeam->front();

    if ((leftTeamFilled && !rightTeamFilled) ||
        (leftTeamFilled && rightTeamFilled && leftFront->getId() < rightFront->getId()))
    {
      cur = leftFront;

      friends = _leftTeam;
      friendsTmp = leftTmp;

      enemies = _rightTeam;
      enemiesTmp = rightTmp;
      enemiesBase = _rightBase;
    }
    else
    {
      cur = rightFront;

      friends = _rightTeam;
      friendsTmp = rightTmp;

      enemies = _leftTeam;
      enemiesTmp = leftTmp;
      enemiesBase = _leftBase;
    }

    if (!cur->getHealth())
    {
      friendsTmp = deathTmp;
      enemiesBase->addMoney(cur->getReward());
    }
    else if (!friendsTmp->empty())
    {
      cur->process(friendsTmp->back());
    }
    else if (!enemiesTmp->empty())
    {
      cur->process(enemiesTmp->front());
    }
    else if (!enemies->empty())
    {
      cur->process(enemies->front());
    }
    else
    {
      cur->process(enemiesBase);
    }

    friends->pop();
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

  if (action)
  {
    _leftBase->process();
    tmp = _leftBase->keyCheck();
    if (tmp)
      _leftTeam->push(tmp);
  }
  _leftBase->render();

  if (action)
  {
    _rightBase->process();
    tmp = _rightBase->keyCheck();
    if (tmp)
      _rightTeam->push(tmp);
  }
  _rightBase->render();
}

void Action::start(void)
{
  std::cout << "Action: строим укрепточки" << std::endl;

  action = true;

  _leftBase = new Base(-96);
  _rightBase = new Base(1088, FLIP_HORIZONTAL);
}

void Action::stop(void)
{
  action = false;
}

void Action::renderer(void)
{
  if (_leftBase)
    _baseRenderer();
  _unitsRenderer();
}

void Action::clear(void)
{
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
