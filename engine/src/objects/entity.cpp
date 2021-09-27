#include "entity.hpp"

#include <iostream>

#include "SDL_image.h"
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
  _texture = nullptr;
  _geometry = new Rect;

  _angle = 0;
  _flip = FLIP_NONE;
  _center = nullptr;
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

  setFlip(entity->_flip);
  setAngle(entity->_angle);

  if (entity->_center)
  {
    _center = new Point;
    _center->x = entity->_center->x;
    _center->y = entity->_center->y;
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

void Entity::setAngle(const double angle)
{
  _angle = angle;
}

void Entity::setCenter(const int x, const int y)
{
  if (!_center)
    _center = new Point;

  _center->x = _geometry->x + x;
  _center->y = _geometry->y + y;
}

void Entity::setFlip(const Flip flip)
{
  _flip = flip;
}

Flip Entity::getFlip(void)
{
  return _flip;
}

void Entity::process(void) {}

void Entity::render(void)
{
  if (!_texture)
    return;

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

  if (_flip || _angle)
  {
    SDL_RendererFlip flip;

    switch (_flip)
    {
    case FLIP_NONE:
      flip = SDL_FLIP_NONE;
      break;
    case FLIP_HORIZONTAL:
      flip = SDL_FLIP_HORIZONTAL;
      break;
    case FLIP_VERTICAL:
      flip = SDL_FLIP_VERTICAL;
      break;
    }

    SDL_Point *center = nullptr;
    if (_center)
    {
      center = new SDL_Point;
      center->x = _center->x;
      center->y = _center->y;
    }

    if (SDL_RenderCopyEx(global::renderer, _texture, tile, geometry, _angle, center, flip))
      std::cout << "SdlWindow: ошибка рендера:" << SDL_GetError() << std::endl;
    
    delete center;
  }
  else if (SDL_RenderCopy(global::renderer, _texture, tile, geometry))
  {
    std::cout << "SdlWindow: ошибка рендера:" << SDL_GetError() << std::endl;
  }
  
  delete tile;
  delete geometry;
}

Entity::~Entity()
{
  std::cout << "Entity: удаление геометрии сущности" << std::endl;
  delete _center;
  delete _geometry;
}
