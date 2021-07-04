#include "globals.hpp"

namespace glob
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
}

Gui *gui = nullptr;
EventSubSystem *events = nullptr;
TextureManager *textures = nullptr;
Font *font = nullptr;
Action *action = nullptr;
std::string *p1 = nullptr, *p2 = nullptr;
