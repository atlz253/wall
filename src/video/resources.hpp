#include "SDL.h"
#include <string>

extern const int SCREEN_WIDTH;  // Ширина окна
extern const int SCREEN_HEIGHT; // Высота окна

/*
    Объект на экране
*/
typedef struct screenObj
{
    SDL_Texture *texture = nullptr; // Текстура объекта
    SDL_Rect *rect = nullptr;       // Геометрия объекта
} screenObj;

extern screenObj 
    *background, // Задний фон
    *brick; // Блок пола

/*
    Пути до ресурсов
*/
extern const char *BACKPATH; // Задний фон
extern const char *BRICKPATH; // Блок пола