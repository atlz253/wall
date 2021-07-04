#include "wall.hpp"

#include <iostream>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "action.hpp"
#include "background.hpp"
#include "globals.hpp"
#include "terrain.hpp"

class SdlSubSystem final
{
public:
  SdlSubSystem()
  {

    std::cout << "SdlSubSystem: инициализация SDL2" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO))
    {
      std::cout << "Ошибка инициализации SDL2:" << SDL_GetError() << std::endl;
      exit(EXIT_FAILURE);
    }

    /*
        Не отключать композитор рабочих столов на linux дистрибутивах
    */
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    std::cout << "SdlSubSystem: инициализация SDL2_Image" << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
      std::cout << "Ошибка инициализации SDL2_Image:" << IMG_GetError() << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "SdlSubSystem: инициализация SDL2_ttf" << std::endl;
    if (TTF_Init())
    {
      std::cout << "Ошибка инициализации SDL2_Image:" << TTF_GetError() << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  ~SdlSubSystem()
  {
    std::cout << "SdlSubSystem: завершение работы SDL2" << std::endl;
    SDL_Quit();

    std::cout << "SdlSubSystem: завершение работы SDL2_Image" << std::endl;
    IMG_Quit();

    std::cout << "SdlSubSystem: завершение работы SDL2_ttf" << std::endl;
    TTF_Quit();
  }
};

SdlSubSystem *sdlSubSystem;

void Main::_gameLoop(void)
{
  Layer *background = new Background(), *terrain = new Terrain();

  SDL_Event *start = new SDL_Event;
  start->type = SDL_USEREVENT;
  start->user.code = MENU_EVENT;
  SDL_PushEvent(start);

  while (events->checkEvents())
  {
    SDL_RenderClear(glob::renderer);

    background->renderer();
    action->renderer();
    terrain->renderer();
    gui->renderer();

    SDL_RenderPresent(glob::renderer);
  }

  delete background;
  delete terrain;
}

Main::Main()
{
  sdlSubSystem = new SdlSubSystem();

  std::cout << "Creating window" << std::endl;
  glob::window = SDL_CreateWindow("wall", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (!glob::window)
  {
    std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  glob::renderer = SDL_CreateRenderer(glob::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!glob::renderer)
    std::cout << "Failed to create renderer:" << SDL_GetError() << std::endl;

  p1 = new std::string;
  p2 = new std::string;

  font = new Font();
  font->open("res/joystix_monospace.ttf");

  events = new EventSubSystem();
  textures = new TextureManager();

  gui = new Gui();
  action = new Action();
}

int Main::run(void)
{
  _gameLoop();

  return 0;
}

Main::~Main()
{
  delete gui;
  delete action;

  SDL_DestroyWindow(glob::window);
  SDL_DestroyRenderer(glob::renderer);

  delete p1;
  delete p2;

  delete font;
  delete events;
  delete textures;

  delete sdlSubSystem;
}
