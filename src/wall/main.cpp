#include "main.hpp"
#include "print.hpp"
#include "entity.hpp"
#include "texture.hpp"
#include "SDL_image.h"
#include "textureManager.hpp"
#include "sky.hpp"

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

    textures->key("background") = new Texture(_renderer, "res/Magic-Cliffs-Environment/PNG/sky.png");
    textures->key("brick") = new Texture(_renderer, "res/sprites/brick.png");

    int aa = 0;
    Entity *_background = new Sky(textures->key("background"));
    Entity *_brick = new Entity(textures->key("brick"), 64, 64, 0, 700);
    Entity *_move = new Entity(textures->key("brick"), 64, 64, aa, 360);

    while (_window->checkEvent())
    {
        /* updateRender(); */
        _renderer->clear();

        *_renderer << _background;

        for (int i = 0; i < 1280 / 64 + 1; i++)
        {
            *_renderer << _brick;
            _brick->setPosition(i * 64, 700);
        }
        _brick->setPosition(0, 700);

        aa += 2;
        _move->setPosition(aa, 360);
        *_renderer << _move;

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