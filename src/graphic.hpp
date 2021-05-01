#ifndef SDLWINDOW
#define SDLWINDOW

#include <SDL2/SDL.h>
#include "logger/logger.hpp"

class SdlWindow
{
private:
    const int _SCREEN_WIDTH = 640;
    const int _SCREEN_HEIGHT = 480;

    SDL_Window *_window = nullptr;
    SDL_Surface *_screenSurface = nullptr;

    Logger *_logger = nullptr;
public:
    /*
        Инициализация графики:
        Logger *logger - объект-логгер, для вывода отладочных сообщений в консоль
    */
    SdlWindow(Logger *logger);

    /*
        Создание окна игры
    */
    void createWindow(void);
};

#endif