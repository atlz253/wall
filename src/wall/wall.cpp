#include "wall.hpp"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "action.hpp"
#include "background.hpp"
#include "entity.hpp"
#include "font.hpp"
#include "globals.hpp"
#include "menu.hpp"
#include "print.hpp"
#include "terrain.hpp"
#include "window.hpp"

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

    printTrace("SdlSubSystem: инициализация SDL2_ttf");
    if (TTF_Init())
    {
      printError("Ошибка инициализации SDL2_Image:", TTF_GetError());
      exit(EXIT_FAILURE);
    }
    font->open("res/joystix_monospace.ttf");
  }

  ~SdlSubSystem()
  {
    printTrace("SdlSubSystem: завершение работы SDL2");
    SDL_Quit();

    printTrace("SdlSubSystem: завершение работы SDL2_Image");
    IMG_Quit();

    printTrace("SdlSubSystem: завершение работы SDL2_ttf");
    TTF_Quit();
  }
};

void Main::_gameLoop(void)
{
  Layer *background = new Background(), *terrain = new Terrain();
  action = new Action();
  gui = new Gui();

  SDL_Event *start = new SDL_Event;
  start->type = SDL_USEREVENT;
  start->user.code = MENU_EVENT;
  SDL_PushEvent(start);

  while (events->checkEvents())
  {
    renderer->clear();

    background->renderer();
    action->renderer();
    terrain->renderer();
    gui->renderer();

    renderer->draw();
  }

  delete background;
  delete terrain;
  delete action;
}

Main::Main() {}

int Main::run(void)
{
  SdlSubSystem *sdlSubSystem = new SdlSubSystem();
  window = new SdlWindow();
  renderer = new Renderer();
  *window >> renderer;

  _gameLoop();

  printTrace("Main: завершение работы подсистемы SDL2");
  delete sdlSubSystem;

  return 0;
}

Main::~Main()  // TODO: удаление всего глобального
{
  printTrace("Main: удаление окна");
  delete window;
}
