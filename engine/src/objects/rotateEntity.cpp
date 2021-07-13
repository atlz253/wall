#include "entity.hpp"

#include <iostream>

#include "global.hpp"

RotateEntity::RotateEntity() : Entity::Entity() {}

RotateEntity::RotateEntity(std::string path, int w, int h, int x, int y, SDL_RendererFlip flip)
    : Entity(path, w, h, x, y)
{
  _center = new SDL_Point;
  _center->x = _geometry->x + _geometry->w / 2;
  _center->y = _geometry->y + _geometry->h / 2;

  _flip = flip;
}

RotateEntity::RotateEntity(std::string path, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH,
                           int tileX, int tileY, SDL_RendererFlip flip)
    : RotateEntity(path, entityW, entityH, entityX, entityY, flip)
{
  setTile(tileX, tileY, tileW, tileH);
}

RotateEntity::RotateEntity(RotateEntity *&entity, SDL_RendererFlip flip, int x, int y) : Entity::Entity()
{
  _texture = entity->_texture;

  setSize(entity->_geometry->w, entity->_geometry->h);
  setPosition(x, y);

  _center = new SDL_Point;
  _center->x = _geometry->x + _geometry->w / 2;
  _center->y = _geometry->y + _geometry->h / 2;

  if (entity->_tile)
  {
    _tile = new SDL_Rect;
    _tile->h = entity->_tile->h;
    _tile->w = entity->_tile->w;
    _tile->x = entity->_tile->x;
    _tile->y = entity->_tile->y;
  }

  _flip = flip;
}

void RotateEntity::render(void)
{
  if (SDL_RenderCopyEx(global::renderer, _texture, _tile, _geometry, _angle, _center, _flip))
    std::cout << "SdlWindow: ошибка рендера:" << SDL_GetError() << std::endl;
}

void RotateEntity::setAngle(const double angle) { _angle = angle; }

void RotateEntity::setCenter(const int x, const int y)
{
  if (!_center)
    _center = new SDL_Point;

  _center->x = _geometry->x + x;
  _center->y = _geometry->y + y;
}

void RotateEntity::setFlip(const SDL_RendererFlip flip) { _flip = flip; }

SDL_RendererFlip RotateEntity::getFlip(void) { return _flip; }

RotateEntity::~RotateEntity() { delete _center; }