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

    _window = _createWindow();
    _renderer = _createRenderer();

    _background = new Entity(_renderer, "res/sprites/background/bg.png", _SCREEN_WIDTH, _SCREEN_HEIGHT, 0, 0);
    _brick = new Entity(_renderer, "res/sprites/brick.png", 64, 64, 0, 700);
    _move = new Entity(_renderer, "res/sprites/brick.png", 64, 64, aa, 360);
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

    for (int i = 0; i < _SCREEN_WIDTH / 64 + 1; i++)
    {
        _brick->renderCopy();
        _brick->setPosition(i * 64, 700);
    }
    _brick->setPosition(0, 700);

    aa += 2;
    _move->setPosition(aa, 360);
    _move->renderCopy();

    SDL_RenderPresent(_renderer);
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(_window);
}