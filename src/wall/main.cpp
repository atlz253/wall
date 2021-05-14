#include "main.hpp"
#include "print.hpp"
#include "action.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "SDL_image.h"
#include "terrain.hpp"
#include "renderer.hpp"
#include "background.hpp"
#include "eventSubSystem.hpp"

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

        /*
            Не отключать композитор рабочих столов на linux дистрибутивах
        */
        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

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
    EventSubSystem *events = new EventSubSystem();
    Layer 
        *background = new Background(_renderer),
        *terrain = new Terrain(_renderer),
        *action = new Action(_renderer);

    while (events->checkEvents())
    {
        _renderer->clear();

        background->renderer();
        action->renderer();
        terrain->renderer();

        _renderer->draw();
    }

    delete events;
}

Main::Main()
{
}

int Main::run(void)
{
    SdlSubSystem *sdlSubSystem = new SdlSubSystem();
    _window = new SdlWindow(); //TODO: SDL_CreateWindowAndRenderer
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