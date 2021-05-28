#ifndef GLOBALS
#define GLOBALS

#include "textureManager.hpp"

class Renderer;

const int SCREEN_WIDTH = 1280;  // Ширина окна
const int SCREEN_HEIGHT = 720;  // Высота окна

extern Renderer *renderer;
extern TextureManager *textures;

#endif
