#include "action.hpp"

#include <iostream>

#include "base.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"

enum baseId
{
  LEFT_BASE_ID = 1,
  RIGHT_BASE_ID = 2
};

Action::Action(Renderer *renderer)  // TODO: убрать параметр renderer
{
  _leftTeam = new std::queue<Unit *>;
  _rightTeam = new std::queue<Unit *>;
  _deathQueue = new std::queue<Unit *>;

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
    Unit *cur = nullptr, *leftFront = _leftTeam->front(), *rightFront = _rightTeam->front();
    bool leftTeamFilled = !_leftTeam->empty(), rightTeamFilled = !_rightTeam->empty();

    if (leftTeamFilled && !leftFront->getHealth())
    {
      cur = leftFront;
      deathTmp->push(cur);
      _leftTeam->pop();
    }
    else if (rightTeamFilled && !rightFront->getHealth())
    {
      cur = rightFront;
      deathTmp->push(cur);
      _rightTeam->pop();
    }
    else if ((leftTeamFilled && !rightTeamFilled) ||
             (leftTeamFilled && rightTeamFilled && leftFront->getId() < rightFront->getId()))
    {
      cur = leftFront;

      if (!leftTmp->empty())
        cur->process(leftTmp->back());
      else if (!rightTeamFilled && !rightTmp->empty())
        cur->process(rightTmp->front());
      else if (rightTeamFilled)
        cur->process(rightFront);
      else
        cur->process(_rightBase);

      leftTmp->push(cur);
      _leftTeam->pop();
    }
    else if ((!leftTeamFilled && rightTeamFilled) ||
             (leftTeamFilled && rightTeamFilled && leftFront->getId() > rightFront->getId()))
    {
      cur = rightFront;

      if (!rightTmp->empty())
        cur->process(rightTmp->back());
      else if (!leftTeamFilled && !leftTmp->empty())
        cur->process(leftTmp->front());
      else if (leftTeamFilled)
        cur->process(leftFront);
      else
        cur->process(_leftBase);

      rightTmp->push(cur);
      _rightTeam->pop();
    }

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
  delete _rightTeam;
  delete _deathQueue;
  _leftTeam = leftTmp;
  _rightTeam = rightTmp;
  _deathQueue = deathTmp;
}

void Action::_baseRenderer(void)
{
  Unit *tmp;

  tmp = _leftBase->keyCheck();
  if (tmp)
    _leftTeam->push(tmp);
  _leftBase->render();


  tmp = _rightBase->keyCheck();
  if (tmp)
    _rightTeam->push(tmp);
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
