#include "graphic.hpp"

SdlWindow::SdlWindow(Logger *logger)
{
    _logger = logger;
    _logger->trace("SdlWindow init");

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        _logger->error(SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void SdlWindow::createWindow(void)
{
    _logger->trace("SdlWindow creating window");
    _window = SDL_CreateWindow(
        "wall",
        SDL_WINDOWPOS_CENTERED_MASK,
        SDL_WINDOWPOS_CENTERED_MASK,
        _SCREEN_WIDTH,
        _SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (_window)
    {
        _screenSurface = SDL_GetWindowSurface(_window);
        SDL_FillRect(
            _screenSurface,
            nullptr,
            SDL_MapRGB(
                _screenSurface->format,
                0xFF,
                0xFF,
                0xFF));

        SDL_UpdateWindowSurface(_window);
    }
    else
    {
        _logger->error(SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

bool SdlWindow::checkEvent()
{
    if(SDL_PollEvent(&_event))
    {
        if(_event.type == SDL_QUIT)
        {
            _logger->trace("SDL_Quit event");
            return false;
        }
    }

    return true;
}

SdlWindow::~SdlWindow()
{
    SDL_FreeSurface(_screenSurface);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}