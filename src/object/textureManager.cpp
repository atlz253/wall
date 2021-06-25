#include "textureManager.hpp"

#include "SDL2/SDL_image.h"
#include "globals.hpp"
#include "print.hpp"
#include "renderer.hpp"

void TextureManager::_loadTexture(std::string path)
{
  printTrace("TextureManager: загрузка текстуры", path);
  SDL_Texture *texture = IMG_LoadTexture(renderer->getRender(), path.c_str());

  if (!texture) printError("TextureManager: не удалось загрузить текстуру.", IMG_GetError());

  _dict[path] = texture;
}

TextureManager::TextureManager() { printTrace("Инициализация менеджера текстур"); }

SDL_Texture *&TextureManager::key(std::string name)
{
  _iterator = _dict.find(name);

  if (_iterator->first != name) _loadTexture(name);

  return _dict[name];
}

TextureManager::~TextureManager()
{
  printTrace("TextureManager: удаление текстур из памяти");
  for (_iterator = _dict.begin(); _iterator != _dict.end(); _iterator++) SDL_DestroyTexture(_iterator->second);
}
