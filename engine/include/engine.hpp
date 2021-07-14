#include "textureManager.hpp"

namespace engine
{
  extern TextureManager *textures; // TODO: remove

  int init(); // TODO: flags?

  int quit();
}

namespace render
{
  int clear();

  void present();
}