#include "entity.hpp"

#include <iostream>

#include "SDL2/SDL_image.h"
#include "global.hpp"
#include "textureManager.hpp"

SDL_Texture *Entity::getTexture(std::string path)
{
  return textures::get(path);
}

Entity::Entity()
{
  std::cout << "Entity: создание сущности" << std::endl;

  _tile = nullptr;
  _geometry = new Rect;
}

Entity::Entity(int w, int h, int x, int y) : Entity()
{
  setSize(w, h);
  setPosition(x, y);
}

Entity::Entity(std::string path, int w, int h, int x, int y) : Entity(w, h, x, y) { _texture = textures::get(path); }

Entity::Entity(std::string path, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX,
               int tileY)
    : Entity(path, entityW, entityH, entityX, entityY)
{
  setTile(tileX, tileY, tileW, tileH);
}

Entity::Entity(Entity *&entity, int x, int y) : Entity::Entity()
{
  _texture = entity->_texture;

  setSize(entity->_geometry->w, entity->_geometry->h);
  setPosition(x, y);

  if (entity->_tile)
  {
    _tile = new Rect;
    _tile->h = entity->_tile->h;
    _tile->w = entity->_tile->w;
    _tile->x = entity->_tile->x;
    _tile->y = entity->_tile->y;
  }
}

void Entity::setSize(int w, int h)
{
  _geometry->w = w;
  _geometry->h = h;
}

void Entity::setPosition(int x, int y)
{
  _geometry->x = x;
  _geometry->y = y;
}

void Entity::setTile(int x, int y, int w, int h)
{
  if (!_tile)
    _tile = new Rect;

  _tile->x = x;
  _tile->y = y;
  _tile->w = w;
  _tile->h = h;
}

void Entity::process(void) {}

void Entity::render(void)
{
  SDL_Rect *geometry = new SDL_Rect, *tile = nullptr;
  geometry->h = _geometry->h;
  geometry->w = _geometry->w;
  geometry->x = _geometry->x;
  geometry->y = _geometry->y;

  if (_tile)
  {
    tile = new SDL_Rect;
    tile->h = _tile->h;
    tile->w = _tile->w;
    tile->x = _tile->x;
    tile->y = _tile->y;
  }

  if (_texture && SDL_RenderCopy(global::renderer, _texture, tile, geometry))
    std::cout << "SdlWindow: ошибка рендера:" << SDL_GetError() << std::endl;

  delete tile;
  delete geometry;
}

Entity::~Entity()
{
  std::cout << "Entity: удаление геометрии сущности" << std::endl;
  delete _geometry;
}
