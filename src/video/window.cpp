#include "window.hpp"
#include "SDL_image.h"

SDL_Window *SdlWindow::_createWindow(void)
{
    _logger->trace("SdlWindow: создание окна");
    SDL_Window *window = SDL_CreateWindow(
        "wall",
        SDL_WINDOWPOS_CENTERED_MASK,
        SDL_WINDOWPOS_CENTERED_MASK,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (window)
    {
        return window;
    }
    else
    {
        _logger->error("SdlWindow: не удалось создать окно:", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Renderer *SdlWindow::_createRenderer(void)
{
    _logger->trace("SdlWindow: создание рендера");
    SDL_Renderer *render = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!render)
        _logger->error("SdlWindow: не удалось создать рендер:", SDL_GetError());

    return render;
}

void SdlWindow::_backgroundInit(void)
{
    background->texture = _loadTexture(BACKPATH);

    SDL_Rect *rect = new SDL_Rect;
    rect->x = 0;
    rect->y = 0;
    rect->w = SCREEN_WIDTH;
    rect->h = SCREEN_HEIGHT;

    background->rect = rect;
}

void SdlWindow::_backgroundRenderer(void)
{
    if (SDL_RenderCopy(_renderer, background->texture, nullptr, background->rect))
        _logger->error("SdlWindow: ошибка рендера заднего фона.", SDL_GetError());
}

SDL_Texture *SdlWindow::_loadTexture(std::string path)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, path.c_str());

    if (!texture)
        _logger->error("SdlWindow: не удалось загрузить текстуру.", IMG_GetError());
    
    return texture;
}

SdlWindow::SdlWindow(Logger *logger)
{
    logger->trace("SdlWindow: начало инициализации");
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

    _window = _createWindow();
    _renderer = _createRenderer();
    _backgroundInit();
}

bool SdlWindow::checkEvent()
{
    _logger->trace("SdlWindow: проверка события");

    while (SDL_PollEvent(&_event)) //TODO: использовать SDL_WaitEvent
    {
        if (_event.type == SDL_QUIT)
        {
            _logger->trace("SdlWindow: SDL_Quit event");
            return false;
        }
    }

    return true;
}

void SdlWindow::updateRenderer(void)
{
    SDL_RenderClear(_renderer);
    _backgroundRenderer();
    SDL_RenderPresent(_renderer);
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}