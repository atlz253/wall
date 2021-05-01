#ifndef SDLWINDOW
#define SDLWINDOW

#include <SDL2/SDL.h>
#include "logger/logger.hpp"

class SdlWindow
{
private:
    const int _SCREEN_WIDTH = 1280;
    const int _SCREEN_HEIGHT = 720;

    SDL_Window *_window = nullptr;
    SDL_Surface *_screenSurface = nullptr;

    /*
        Обработчик событий
    */
    SDL_Event _event;

    /*
        "Поверхность экрана", которая хранит задний фон игры
    */
    SDL_Surface *_background_1 = nullptr,
                *_background_2 = nullptr,
                *_background_3 = nullptr;

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

    /*
        Проверка событий SDL
    */
    bool checkEvent(void);

    ~SdlWindow();
};

#endif