#ifndef SDLWINDOW
#define SDLWINDOW

#include "SDL.h"
#include "logger.hpp"

class SdlWindow
{
private:
    const int _SCREEN_WIDTH = 1280; // Ширина окна
    const int _SCREEN_HEIGHT = 720; // Высота окна

    SDL_Window *_window = nullptr;         // Основное окно игры
    SDL_Renderer *_renderer = nullptr;     // Рендер окна
    SDL_Surface *_screenSurface = nullptr; // Основная "поверхность экрана"

    SDL_Event _event; // Обработчик событий

    SDL_Surface *_background = nullptr; // задний фон

    Logger *_logger = nullptr;

    /*
        Создание окна
    */
    SDL_Window *_createWindow(void);

    /*
        Инициализация рендера
    */
    SDL_Renderer *_createRenderer(void);

    /*
        Загрузка PNG изображений
    */
    SDL_Surface *_loadPNG(std::string path);

public:
    /*
        Инициализация графики:
        Logger *logger - объект-логгер, для вывода отладочных сообщений в консоль
    */
    SdlWindow(Logger *logger);

    /*
        Инициализация
    */
    void init(void);

    /*
        Проверка событий SDL
    */
    bool checkEvent(void);

    ~SdlWindow();
};

#endif