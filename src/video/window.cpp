#include "print.hpp"
#include "window.hpp"
#include "SDL_image.h"
#include "renderer.hpp"

SdlWindow::SdlWindow()
{
    printTrace("SdlWindow: создание окна");
    _window = SDL_CreateWindow(
        "wall",
        SDL_WINDOWPOS_CENTERED_MASK,
        SDL_WINDOWPOS_CENTERED_MASK,
        _SCREEN_WIDTH,
        _SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (!_window)
    {
        printError("SdlWindow: не удалось создать окно:", SDL_GetError());
        exit(EXIT_FAILURE);
    }
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

void SdlWindow::operator>> (Renderer *renderer)
{
    printTrace("SdlWindow: создание рендера");
    renderer->_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer->_renderer)
        printError("SdlWindow: не удалось создать рендер:", SDL_GetError());
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(_window);
}