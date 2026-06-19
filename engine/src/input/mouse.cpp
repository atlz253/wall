#include "mouse.hpp"

#include "SDL.h"

#include "global.hpp"

namespace mouse
{
    Point Position(void)
    {
        Point position;
        float logicalX = 0;
        float logicalY = 0;

        SDL_GetMouseState(&position.x, &position.y);
        SDL_RenderWindowToLogical(global::renderer, position.x, position.y, &logicalX, &logicalY);
        position.x = static_cast<INT32>(logicalX);
        position.y = static_cast<INT32>(logicalY);

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
