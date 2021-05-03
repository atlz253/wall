#ifndef SDLWINDOW
#define SDLWINDOW

#include "logger.hpp"
#include "resources.hpp"

class SdlWindow final
{
private:
    SDL_Window *_window = nullptr;     // Основное окно игры
    SDL_Renderer *_renderer = nullptr; // Рендер окна

    SDL_Event _event; // Обработчик событий

    Logger *_logger = nullptr;

    /*
        Создание окна
    */
    SDL_Window *_createWindow(void);

    /*
        Создание рендера
    */
    SDL_Renderer *_createRenderer(void);

    /*
        Загрузка текстур
    */
    SDL_Texture *_loadTexture(std::string path);

    /*
        Инициализация заднего фона
    */
    void _backgroundInit(void);

    /*
        Рендер заднего фона
    */
    void _backgroundRenderer(void);
public:
    /*
        Инициализация окна:
        Logger *logger - объект-логгер, для вывода отладочных сообщений в консоль
    */
    SdlWindow(Logger *logger);

    /*
        Проверка событий SDL
    */
    bool checkEvent(void);

    /*
        Обновление рендера
    */
    void updateRenderer(void);

    ~SdlWindow();
};

#endif