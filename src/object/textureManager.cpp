#include "textureManager.hpp"

#include "SDL2/SDL_image.h"
#include "globals.hpp"
#include "print.hpp"
#include "renderer.hpp"

TextureManager::TextureManager() { printTrace("Инициализация менеджера текстур"); }

void TextureManager::loadTexture(std::string path)
{
  printTrace("TextureManager: загрузка текстуры", path);
  SDL_Texture *texture = IMG_LoadTexture(renderer->getRender(), path.c_str()); //TODO: есть ли уже текстура?

  if (!texture) printError("TextureManager: не удалось загрузить текстуру.", IMG_GetError());

  _dict[path] = texture;
}

void TextureManager::loadTexture(std::string name, std::string path)
{
  printTrace("TextureManager: загрузка текстуры", path);
  SDL_Texture *texture = IMG_LoadTexture(renderer->getRender(), path.c_str()); //TODO: есть ли уже текстура?

  if (!texture) printError("TextureManager: не удалось загрузить текстуру.", IMG_GetError());

  _dict[name] = texture;
}

SDL_Texture *&TextureManager::key(std::string name)
{
  _iterator = _dict.find(name);

  if (_iterator->first != name) _dict[name] = nullptr;  // на всякий случай создаем пару ключ:значение

  return _dict[name];
}

TextureManager::~TextureManager()
{
  printTrace("TextureManager: удаление текстур из памяти");
  for (_iterator = _dict.begin(); _iterator != _dict.end(); _iterator++) SDL_DestroyTexture(_iterator->second);
}
