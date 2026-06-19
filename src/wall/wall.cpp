#include "wall.hpp"

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "event.hpp"
#include "engine.hpp"

#include "action.hpp"
#include "background.hpp"
#include "globals.hpp"
#include "storage.hpp"
#include "terrain.hpp"

void Main::_gameLoop(void)
{
  gui->menu();

  while (_frame())
    ;
}

Main::Main()
{
  engine::init();
  storage::init();

  gui = new Gui();
  action = new Action();
  _background = new Background();
  _terrain = new Terrain();
}

bool Main::_frame(void)
{
  if (!events::check())
  {
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
    return false;
  }

  render::clear();

  _background->renderer();
  _terrain->renderer();
  action->renderer();
  gui->renderer();

  render::present();

  return true;
}

int Main::run(void)
{
#ifdef __EMSCRIPTEN__
  gui->menu();
  emscripten_set_main_loop_arg(
      [](void *arg)
      {
        static_cast<Main *>(arg)->_frame();
      },
      this, 0, 1);
  return 0;
#else
  _gameLoop();
  return 0;
#endif
}

Main::~Main()
{
  delete _background;
  delete _terrain;
  delete gui;
  delete action;

  engine::quit();
}
