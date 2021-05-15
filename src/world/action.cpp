#include "base.hpp"
#include "print.hpp"
#include "action.hpp"
#include "globals.hpp"
#include "knight.hpp"

Action::Action(Renderer *renderer)
{
    printTrace("Action: строим укрепточки");
    _list.push_back(new Base(-96, SDL_FLIP_HORIZONTAL));

    _list.push_back(new Knight());
    _list.push_back(new Base(1088));
}

void Action::renderer(void)
{
    for (_iterator = _list.begin(); _iterator != _list.end(); _iterator++)
    {
        (*_iterator)->process(*++_iterator);
        _iterator--;
        (*_iterator)->renderer();
    }
}