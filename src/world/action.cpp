#include "action.hpp"

#include <iostream>

#include "base.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"

Action::Action(Renderer *renderer)  // TODO: убрать параметр renderer
{
  _leftTeam = new std::queue<Unit *>;
  _rightTeam = new std::queue<Unit *>;
  _deathQueue = new std::queue<Unit *>;  // TODO: исчезновение трупов

  printTrace("Action: строим укрепточки");

  _leftBase = new Base(-96);
  _rightBase = new Base(1088, SDL_FLIP_HORIZONTAL);
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
  Unit *tmp;

  tmp = _leftBase->keyCheck();
  if (tmp) _leftTeam->push(tmp);
  _leftBase->render();

  tmp = _rightBase->keyCheck();
  if (tmp) _rightTeam->push(tmp);
  _rightBase->render();
}

void Action::renderer(void)
{
  _baseRenderer();
  _unitsRenderer();
}

Action::~Action()
{
  // FIXME: реализовать деструктор
}
