#ifndef ENGINE
#define ENGINE

namespace engine
{
  int init(); // TODO: flags?

  int quit();
}

namespace render
{
  int clear();

  void present();
}

#endif // ENGINE