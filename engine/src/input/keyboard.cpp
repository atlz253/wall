#include "keyboard.hpp"

#include "SDL2/SDL.h"

namespace keyboard
{
    keys state(int *numkeys)
    {
        return SDL_GetKeyboardState(numkeys);
    }
}