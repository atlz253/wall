#include "wall.hpp"

#include <iostream>

#include "engine.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "action.hpp"
#include "background.hpp"
#include "globals.hpp"
#include "terrain.hpp"

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
  engine::init();

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

  engine::quit();
}
