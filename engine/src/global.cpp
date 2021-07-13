#include "global.hpp"

#include "SDL2/SDL.h"

namespace global
{
    SDL_Window *window = nullptr; // TODO: try initialization in engine::init()
    SDL_Renderer *renderer = nullptr;
}