#include "keyboard.hpp"

#include "SDL.h"

namespace keyboard
{
    keys state(int *numkeys)
    {
        return SDL_GetKeyboardState(numkeys);
    }
}