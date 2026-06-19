/*
    Точка входа в программу
*/

#include "wall.hpp"

int main(void)
{
#ifdef __EMSCRIPTEN__
  Main *app = new Main();
  return app->run();
#else
  return Main().run();
#endif
}
