#include "wall.hpp"

#include <iostream>

#include "event.hpp"
#include "engine.hpp"

#include "action.hpp"
#include "background.hpp"
#include "globals.hpp"
#include "terrain.hpp"

void Main::_gameLoop(void)
{
  Layer *background = new Background(), *terrain = new Terrain();

  gui->menu();

  while (events::check())
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

  engine::quit();
}
