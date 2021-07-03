#include "entity.hpp"

#include "SDL2/SDL_image.h"
#include "globals.hpp"
#include "print.hpp"
#include "window.hpp"

Entity::Entity()
{
  printTrace("Entity: создание сущности");
  _geometry = new SDL_Rect;
}

Entity::Entity(int w, int h, int x, int y) : Entity()
{
  setSize(w, h);
  setPosition(x, y);
}

Entity::Entity(std::string path, int w, int h, int x, int y) : Entity(w, h, x, y) { _texture = textures->key(path); }

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
    _tile = new SDL_Rect;
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
  if (!_tile) _tile = new SDL_Rect;

  _tile->x = x;
  _tile->y = y;
  _tile->w = w;
  _tile->h = h;
}

void Entity::process(void) {}

void Entity::render(void)
{
  if (_texture && SDL_RenderCopy(renderer, _texture, _tile, _geometry))
    printError("SdlWindow: ошибка рендера.", SDL_GetError());
}

Entity::~Entity()
{
  printTrace("Entity: удаление геометрии сущности");
  delete _geometry;
}
