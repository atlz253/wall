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

  _leftTeam->push(new Knight(700));
  _leftTeam->push(new Knight(600));
  _leftTeam->push(new Knight(500));
  _leftTeam->push(new Knight(400));

  //  _add(new Knight(300));
  _rightTeam->push(new Knight(800, SDL_FLIP_HORIZONTAL));
  _rightTeam->push(new Knight(1000, SDL_FLIP_HORIZONTAL));
}

void Action::renderer(void)
{
  std::queue<Unit *> *leftTmp = new std::queue<Unit *>;
  std::queue<Unit *> *rightTmp = new std::queue<Unit *>;
  std::queue<Unit *> *deathTmp = new std::queue<Unit *>;

  _leftBase->render();
  _rightBase->render();

  while (!_leftTeam->empty() || !_rightTeam->empty())
  {
    Unit *cur = nullptr;

    if (!_leftTeam->empty())
    {
      if (!_leftTeam->front()->getHealth())
      {
        cur = _leftTeam->front();
        deathTmp->push(cur);
        _leftTeam->pop();
      }
      else if (!_rightTeam->empty())
      {
        if (_leftTeam->front()->getId() > _rightTeam->front()->getId())
        {
          cur = _rightTeam->front();

          if (!rightTmp->empty())
            cur->process(rightTmp->back());
          else if (!leftTmp->empty() && _leftTeam->empty())
            cur->process(leftTmp->front());
          else if (!_leftTeam->empty())
            cur->process(_leftTeam->front());
          else
            cur->process(_leftBase);

          rightTmp->push(cur);
          _rightTeam->pop();
        }
        else
        {
          cur = _leftTeam->front();

          if (!leftTmp->empty())
            cur->process(leftTmp->back());
          else if (!rightTmp->empty() && _rightTeam->empty())
            cur->process(rightTmp->front());
          else if (!_rightTeam->empty())
            cur->process(_rightTeam->front());
          else
            cur->process(_rightBase);

          leftTmp->push(cur);
          _leftTeam->pop();
        }
      }
      else
      {
        cur = _leftTeam->front();

        if (!leftTmp->empty())
          cur->process(leftTmp->back());
        else if (!rightTmp->empty() && _rightTeam->empty())
          cur->process(rightTmp->front());
        else if (!_rightTeam->empty())
          cur->process(_rightTeam->front());
        else
          cur->process(_rightBase);

        leftTmp->push(cur);
        _leftTeam->pop();
      }
    }
    else
    {
      if (!_rightTeam->empty())
      {
        if (!_rightTeam->front()->getHealth())
        {
          cur = _rightTeam->front();
          deathTmp->push(cur);
          _rightTeam->pop();
        }
        else
        {
          cur = _rightTeam->front();

          if (!rightTmp->empty())
            cur->process(rightTmp->back());
          else if (!leftTmp->empty() && _leftTeam->empty())
            cur->process(leftTmp->front());
          else if (!_leftTeam->empty())
            cur->process(_leftTeam->front());
          else
            cur->process(_leftBase);

          rightTmp->push(cur);
          _rightTeam->pop();
        }
      }
      else
      {
        break;
      }
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

Action::~Action()
{
  // FIXME: реализовать деструктор
}
