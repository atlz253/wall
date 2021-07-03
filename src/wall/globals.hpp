#ifndef GLOBALS
#define GLOBALS

#include <string>

#include "input.hpp"
#include "action.hpp"
#include "eventSubSystem.hpp"
#include "font.hpp"
#include "gui.hpp"
#include "renderer.hpp"
#include "textureManager.hpp"
#include "window.hpp"

typedef struct record
{
  std::string name;
  unsigned int score;
} record;

const int SCREEN_WIDTH = 1280;  // Ширина окна
const int SCREEN_HEIGHT = 720;  // Высота окна

extern Window *window;
extern Gui *gui;
extern Renderer *renderer;
extern EventSubSystem *events;
extern TextureManager *textures;
extern Font *font;
extern Action *action;
extern std::string *p1, *p2;

#endif
