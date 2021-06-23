#ifndef GLOBALS
#define GLOBALS

#include "action.hpp"
#include "eventSubSystem.hpp"
#include "font.hpp"
#include "gui.hpp"
#include "renderer.hpp"
#include "textureManager.hpp"
#include "window.hpp"

typedef std::uint8_t UINT8;
typedef std::uint16_t UINT16;

const int SCREEN_WIDTH = 1280;  // Ширина окна
const int SCREEN_HEIGHT = 720;  // Высота окна

extern SdlWindow *window;
extern Gui *gui;
extern Renderer *renderer;
extern EventSubSystem *events;
extern TextureManager *textures;
extern Font *font;
extern Action *action;

#endif
