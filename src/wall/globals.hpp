#ifndef GLOBALS
#define GLOBALS

#include <string>

#include "input.hpp"
#include "action.hpp"
#include "eventSubSystem.hpp"
#include "font.hpp"
#include "gui.hpp"

const int SCREEN_WIDTH = 1280; // TODO: remove
const int SCREEN_HEIGHT = 720; // TODO: remove

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct record
{
  std::string name;
  unsigned int score;
} record;

extern Gui *gui;
extern EventSubSystem *events;
extern Action *action;

#endif
