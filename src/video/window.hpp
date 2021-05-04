#ifndef SDLWINDOW
#define SDLWINDOW

#include "entity.hpp"

/*
    Объект класса содержит окно, созданное средствами SDL2
*/
class SdlWindow final
{
private:
    const int _SCREEN_WIDTH = 1280;
    const int _SCREEN_HEIGHT = 720;

    SDL_Window *_window = nullptr;     // Основное окно игры
    SDL_Renderer *_renderer = nullptr; // Текущий кадр окна

    SDL_Event _event; // Обработчик событий

    Entity *_background = nullptr; // УБРАТЬ! Сущность заднего фона
    Entity *_brick = nullptr; // УБРАТЬ! Сущность пола
    Entity *_move = nullptr; // УБРАТЬ!
    int aa = 0;

    /*
        Создание окна
    */
    SDL_Window *_createWindow(void);

    /*
        Создание рендера
    */
    SDL_Renderer *_createRenderer(void);

public:
    /*
        Инициализация окна
    */
    SdlWindow();

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