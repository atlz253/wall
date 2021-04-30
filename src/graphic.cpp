#include <iostream>
#include <SDL2/SDL.h>
#include "ccolors.h"

class SdlWindow
{
private:
    const int _SCREEN_WIDTH = 640;
    const int _SCREEN_HEIGHT = 480;

    SDL_Window *_window = nullptr;
    SDL_Surface *_screenSurface = nullptr;

public:
    SdlWindow()
    {
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            std::cout << ccolors::RED << "SDL_Init Error: " << SDL_GetError() << ccolors::WHITE << std::endl; // TODO: свой логгер
            exit(EXIT_FAILURE);
        }
    }

    void createWindow(void)
    {
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
            
            SDL_Delay(10000);
        }
        else
        {
            std::cout << ccolors::RED << "SDL_CreateWindow Error: " << SDL_GetError() << ccolors::WHITE << std::endl; // TODO: свой логгер
            exit(EXIT_FAILURE);
        }
    }
};