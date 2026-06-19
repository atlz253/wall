#ifndef ENGINE
#define ENGINE

#include "type.hpp"

namespace engine
{
  bool init(INT32 w = 1280, INT32 h = 720); // TODO: flags? + window name

  bool quit();
}

namespace render
{
  bool clear();

  void present();
}

#endif // ENGINE