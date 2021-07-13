#include "textureManager.hpp"

#include <iostream>

#include "SDL2/SDL_image.h"
#include "global.hpp"

void TextureManager::_loadTexture(std::string path)
{
  std::cout << "TextureManager: загрузка текстуры" << path << std::endl;
  SDL_Texture *texture = IMG_LoadTexture(global::renderer, path.c_str());

  if (!texture)
    std::cout << "TextureManager: не удалось загрузить текстуру." << IMG_GetError() << std::endl;

  _dict[path] = texture;
}

TextureManager::TextureManager()
{
  std::cout << "Инициализация менеджера текстур" << std::endl;
}

SDL_Texture *&TextureManager::key(std::string name)
{
  _iterator = _dict.find(name);

  if (_iterator->first != name)
    _loadTexture(name);

  return _dict[name];
}

TextureManager::~TextureManager()
{
  std::cout << "TextureManager: удаление текстур из памяти" << std::endl;
  for (_iterator = _dict.begin(); _iterator != _dict.end(); _iterator++)
    SDL_DestroyTexture(_iterator->second);
}
