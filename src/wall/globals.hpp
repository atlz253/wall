#ifndef GLOBALS
#define GLOBALS

#include "gui.hpp"
#include "renderer.hpp"
#include "textureManager.hpp"
#include "eventSubSystem.hpp"

const int SCREEN_WIDTH = 1280;  // Ширина окна
const int SCREEN_HEIGHT = 720;  // Высота окна

extern Gui *gui;
extern Renderer *renderer;
extern EventSubSystem *events;
extern TextureManager *textures;

#endif
