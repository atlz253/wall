#include "graphic.hpp"
#include "SDL_image.h"

SDL_Window *SdlWindow::_createWindow(void)
{
    _logger->trace("SdlWindow: создание окна");
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
        _logger->error("Не удалось создать окно:", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Renderer *SdlWindow::_createRenderer(void)
{
    SDL_Renderer *render = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!render)
        _logger->error("Не удалось создать рендер:", SDL_GetError());
    
    return render;
}

SDL_Surface *SdlWindow::_loadPNG(std::string path)
{
    SDL_Surface
        *loadedSurface = IMG_Load(path.c_str()),
        *optimizedSurface = nullptr;

    if (loadedSurface)
    {
        optimizedSurface = SDL_ConvertSurface(
            loadedSurface,
            _screenSurface->format,
            0);

        if (!optimizedSurface)
            _logger->error("Не удалось оптимизировать PNG:", IMG_GetError(), path);

        SDL_FreeSurface(loadedSurface);
    }
    else
    {
        _logger->error("Не удалось загрузить PNG:", IMG_GetError());
    }

    return optimizedSurface;
}

SdlWindow::SdlWindow(Logger *logger)
{
    _logger = logger;

    _logger->trace("SdlWindow: инициализация SDL2");
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        _logger->error(SDL_GetError());
        exit(EXIT_FAILURE);
    }

    _logger->trace("SdlWindow: инициализация SDL2_Image");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        _logger->error(IMG_GetError());
        exit(EXIT_FAILURE);
    }
}

void SdlWindow::init(void)
{
    _logger->trace("SdlWindow: начало инициализации");
    _window = _createWindow();
    _screenSurface = SDL_GetWindowSurface(_window);
    // _renderer = _createRenderer();

    _background = _loadPNG("res/sprites/background/bg.png"); // TODO: удаление поверхностей фона

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = _SCREEN_WIDTH;
    stretchRect.h = _SCREEN_HEIGHT;
    SDL_BlitScaled(
        _background,
        nullptr,
        _screenSurface,
        &stretchRect);
    
    SDL_UpdateWindowSurface(_window);
}

bool SdlWindow::checkEvent()
{
    if (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            _logger->trace("SdlWindow: SDL_Quit event");
            return false;
        }
    }

    return true;
}

SdlWindow::~SdlWindow()
{
    SDL_FreeSurface(_screenSurface);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}