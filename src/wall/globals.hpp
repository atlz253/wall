#ifndef GLOBALS
#define GLOBALS

#include <string>

#include "input.hpp"
#include "action.hpp"
#include "eventSubSystem.hpp"
#include "font.hpp"
#include "gui.hpp"
#include "textureManager.hpp"

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct record
{
  std::string name;
  unsigned int score;
} record;

const int SCREEN_WIDTH = 1280; // Ширина окна
const int SCREEN_HEIGHT = 720; // Высота окна
namespace glob
{
  extern SDL_Window *window;
  extern SDL_Renderer *renderer;
}

extern Gui *gui;
extern EventSubSystem *events;
extern TextureManager *textures;
extern Font *font;
extern Action *action;
extern std::string *p1, *p2;

#endif
