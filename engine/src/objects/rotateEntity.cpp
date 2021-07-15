#include "entity.hpp"

#include <iostream>

#include "SDL2/SDL.h"
#include "global.hpp"

RotateEntity::RotateEntity() : Entity::Entity() {}

RotateEntity::RotateEntity(std::string path, int w, int h, int x, int y, Flip flip)
    : Entity(path, w, h, x, y)
{
  _center = new Point;
  _center->x = _geometry->x + _geometry->w / 2;
  _center->y = _geometry->y + _geometry->h / 2;

  _flip = flip;
}

RotateEntity::RotateEntity(std::string path, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH,
                           int tileX, int tileY, Flip flip)
    : RotateEntity(path, entityW, entityH, entityX, entityY, flip)
{
  setTile(tileX, tileY, tileW, tileH);
}

RotateEntity::RotateEntity(RotateEntity *&entity, Flip flip, int x, int y) : Entity::Entity()
{
  _texture = entity->_texture;

  setSize(entity->_geometry->w, entity->_geometry->h);
  setPosition(x, y);

  _center = new Point;
  _center->x = _geometry->x + _geometry->w / 2;
  _center->y = _geometry->y + _geometry->h / 2;

  if (entity->_tile)
  {
    _tile = new Rect;
    _tile->h = entity->_tile->h;
    _tile->w = entity->_tile->w;
    _tile->x = entity->_tile->x;
    _tile->y = entity->_tile->y;
  }

  _flip = flip;
}

void RotateEntity::render(void)
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

  SDL_Point *center = nullptr;
  if (_center)
  {
    center = new SDL_Point;
    center->x = _center->x;
    center->y = _center->y;
  }

  if (_texture && SDL_RenderCopyEx(global::renderer, _texture, tile, geometry, _angle, center, flip))
    std::cout << "SdlWindow: ошибка рендера:" << SDL_GetError() << std::endl;

  delete tile;
  delete center;
  delete geometry;
}

void RotateEntity::setAngle(const double angle) { _angle = angle; }

void RotateEntity::setCenter(const int x, const int y)
{
  if (!_center)
    _center = new Point;

  _center->x = _geometry->x + x;
  _center->y = _geometry->y + y;
}

void RotateEntity::setFlip(const Flip flip) { _flip = flip; }

Flip RotateEntity::getFlip(void) { return _flip; }

RotateEntity::~RotateEntity() { delete _center; }
