#include "resources.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

screenObj 
    *background = new screenObj,
    *brick = new screenObj;

const char *BACKPATH = "res/sprites/background/bg.png";
const char *BRICKPATH = "res/sprites/brick.png";