#include "textureManager.hpp"
#include "font.hpp"

namespace engine
{
  extern TextureManager *textures; // TODO: remove
  extern Font *font; // TODO: remove

  int init(); // TODO: flags?

  int quit();
}

namespace render
{
  int clear();

  void present();
}