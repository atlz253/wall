#include "SDL.h"
#include <string>

extern const int SCREEN_WIDTH; // Ширина окна
extern const int SCREEN_HEIGHT; // Высота окна

/*
    Задний фон
*/
struct background
{
    SDL_Texture *back = nullptr;  // Задний план
    SDL_Rect *backRect = nullptr; // Геометрия заднего плана
};
extern struct background *background;

extern const char *BACKPATH; // расположение изображения заднего плана
