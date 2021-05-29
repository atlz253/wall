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

  printTrace("Action: строим укрепточки");
  _leftTeam->push(new Base(-96));
  _rightTeam->push(new Base(1088, SDL_FLIP_HORIZONTAL));

  _leftTeam->push(new Knight(700));
//  _leftTeam->push(new Knight(400));

  //  _add(new Knight(300));
    _rightTeam->push(new Knight(800, SDL_FLIP_HORIZONTAL));
  //  _add(new Knight(1000, SDL_FLIP_HORIZONTAL));
}

void Action::renderer(void)
{
  std::queue<Unit *> *_leftTmp = new std::queue<Unit *>;
  std::queue<Unit *> *_rightTmp = new std::queue<Unit *>;

  while (!_leftTeam->empty() || !_rightTeam->empty())
  {
    Unit *cur = nullptr;

    if (!_leftTeam->empty())
    {
      if (!_rightTeam->empty())
      {
        if (_leftTeam->front()->getId() > _rightTeam->front()->getId())
        {
          cur = _rightTeam->front();

          if (!_rightTmp->empty() && _rightTmp->back()->getId() != RIGHT_BASE_ID)
            cur->process(_rightTmp->back());
          else if (!_leftTmp->empty() && (_leftTeam->empty() || _leftTeam->back()->getId() != LEFT_BASE_ID))
            cur->process(_leftTmp->back());
          else
            cur->process(_leftTeam->front());

          _rightTmp->push(cur);
          _rightTeam->pop();
        }
        else
        {
          cur = _leftTeam->front();

          if (!_leftTmp->empty() && _leftTmp->back()->getId() != LEFT_BASE_ID)
            cur->process(_leftTmp->back());
          else if (!_rightTmp->empty() && (_rightTeam->empty() || _rightTmp->back()->getId() != RIGHT_BASE_ID))
            cur->process(_rightTmp->back());
          else
            cur->process(_rightTeam->front());

          _leftTmp->push(cur);
          _leftTeam->pop();
        }
      }
      else
      {
        cur = _leftTeam->front();

        if (!_leftTmp->empty() && _leftTmp->back()->getId() != LEFT_BASE_ID)
          cur->process(_leftTmp->back());
        else if (!_rightTmp->empty() && (_rightTeam->empty() || _rightTmp->back()->getId() != RIGHT_BASE_ID))
          cur->process(_rightTmp->back());
        else
          cur->process(_rightTeam->front());

        _leftTmp->push(cur);
        _leftTeam->pop();
      }
    }
    else
    {
      if (!_rightTeam->empty())
      {
        cur = _rightTeam->front();

        if (!_rightTmp->empty() && _rightTmp->back()->getId() != RIGHT_BASE_ID)
          cur->process(_rightTmp->back());
        else if (!_leftTmp->empty() && (_leftTeam->empty() || _leftTeam->back()->getId() != LEFT_BASE_ID))
          cur->process(_leftTmp->back());
        else
          cur->process(_leftTeam->front());

        _rightTmp->push(cur);
        _rightTeam->pop();
      }
      else
      {
        break;
      }
    }

    cur->render();
  }

  delete _leftTeam;
  delete _rightTeam;
  _leftTeam = _leftTmp;
  _rightTeam = _rightTmp;
}

Action::~Action()
{
  // FIXME: реализовать деструктор
}
