#include "mouse.hpp"

#include "SDL.h"

namespace mouse
{
    Point Position(void)
    {
        Point position;

        SDL_GetMouseState(&position.x, &position.y);

        return position;
    }

    bool LeftClick(void)
    {
        if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
            return true;
        else
            return false;
    }
}
