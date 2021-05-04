#include "print.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "SDL_image.h"

SDL_Window *SdlWindow::_createWindow(void)
{
    printTrace("SdlWindow: создание окна");
    SDL_Window *window = SDL_CreateWindow(
        "wall",
        SDL_WINDOWPOS_CENTERED_MASK,
        SDL_WINDOWPOS_CENTERED_MASK,
        _SCREEN_WIDTH,
        _SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (window)
    {
        return window;
    }
    else
    {
        printError("SdlWindow: не удалось создать окно:", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Renderer *SdlWindow::_createRenderer(void)
{
    printTrace("SdlWindow: создание рендера");
    SDL_Renderer *render = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!render)
        printError("SdlWindow: не удалось создать рендер:", SDL_GetError());
    
    return render;
}

SdlWindow::SdlWindow()
{
    printTrace("SdlWindow: начало инициализации");

    printTrace("SdlWindow: инициализация SDL2");
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printError(SDL_GetError());
        exit(EXIT_FAILURE);
    }

    printTrace("SdlWindow: инициализация SDL2_Image");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printError(IMG_GetError());
        exit(EXIT_FAILURE);
    }

    _window = _createWindow();
    _renderer = _createRenderer();

    _background = new Entity(_renderer, "res/sprites/background/bg.png", _SCREEN_WIDTH, _SCREEN_HEIGHT, 0, 0);
}

bool SdlWindow::checkEvent()
{
    printTrace("SdlWindow: проверка события");

    while (SDL_PollEvent(&_event)) //TODO: использовать SDL_WaitEvent
    {
        if (_event.type == SDL_QUIT)
        {
            printTrace("SdlWindow: SDL_Quit event");
            return false;
        }
    }

    return true;
}

void SdlWindow::updateRenderer(void)
{
    SDL_RenderClear(_renderer);
    _background->renderCopy();
    SDL_RenderPresent(_renderer);
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}