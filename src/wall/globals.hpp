#ifndef GLOBALS
#define GLOBALS

#include "eventSubSystem.hpp"
#include "gui.hpp"
#include "renderer.hpp"
#include "textureManager.hpp"

typedef std::uint8_t UINT8;
typedef std::uint16_t UINT16;

const int SCREEN_WIDTH = 1280;  // Ширина окна
const int SCREEN_HEIGHT = 720;  // Высота окна

extern Gui *gui;
extern Renderer *renderer;
extern EventSubSystem *events;
extern TextureManager *textures;

#endif
