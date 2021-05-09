#include "main.hpp"
#include "print.hpp"
#include "entity.hpp"
#include "texture.hpp"
#include "SDL_image.h"
#include "textureManager.hpp"
#include "background.hpp"

class SdlSubSystem final
{
public:
    SdlSubSystem()
    {
        printTrace("SdlSubSystem: инициализация SDL2");
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            printError("Ошибка инициализации SDL2:", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        printTrace("SdlSubSystem: инициализация SDL2_Image");
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            printError("Ошибка инициализации SDL2_Image:", IMG_GetError());
            exit(EXIT_FAILURE);
        }
    }

    ~SdlSubSystem()
    {
        printTrace("SdlSubSystem: завершение работы SDL2");
        SDL_Quit();

        printTrace("SdlSubSystem: завершение работы SDL2_Image");
        IMG_Quit();
    }
};

void Main::_gameLoop(void)
{
    TextureManager *textures = new TextureManager();

    Entity *_background = new Background(textures, _renderer);

    while (_window->checkEvent())
    {
        _renderer->clear();

        *_renderer << _background;

        _renderer->draw();
    }

    delete textures;
}

Main::Main()
{
}

int Main::run(void)
{
    SdlSubSystem *sdlSubSystem = new SdlSubSystem();
    _window = new SdlWindow();
    _renderer = new Renderer();
    *_window >> _renderer;

    _gameLoop();

    printTrace("Main: завершение работы подсистемы SDL2");
    delete sdlSubSystem;

    return 0;
}

Main::~Main()
{
    printTrace("Main: удаление окна");
    delete _window;
}