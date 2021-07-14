#include "wall.hpp"

#include <iostream>

#include "engine.hpp"
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
    render::clear();

    background->renderer();
    action->renderer();
    terrain->renderer();
    gui->renderer();

    render::present();
  }

  delete background;
  delete terrain;
}

Main::Main()
{
  engine::init();

  events = new EventSubSystem();

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

  delete events;

  engine::quit();
}
