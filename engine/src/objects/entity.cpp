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

Entity::Entity(UINT16 w, UINT16 h, INT16 x, INT16 y) : Entity()
{
    SetSize(w, h);
    SetPosition(x, y);
}

Entity::Entity(std::string path, UINT16 w, UINT16 h, INT16 x, INT16 y) : Entity(w, h, x, y) { _texture = textures::get(path); }

Entity::Entity(std::string path, UINT16 entityW, UINT16 entityH, INT16 entityX, INT16 entityY, UINT16 tileW, UINT16 tileH, INT16 tileX,
               INT16 tileY)
    : Entity(path, entityW, entityH, entityX, entityY)
{
    SetTile({tileX, tileY, tileW, tileH});
}

Entity::Entity(Entity *&entity, int x, int y) : Entity::Entity()
{
    _texture = entity->_texture;

    SetSize(entity->_geometry->w, entity->_geometry->h);
    SetPosition(x, y);

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

UINT16 Entity::GetWidth(void)
{
    return _geometry->w;
}

UINT16 Entity::GetHeight(void)
{
    return _geometry->h;
}

void Entity::SetWidth(UINT16 w)
{
    _geometry->w = w;
}

void Entity::SetHeight(UINT16 h)
{
    _geometry->h = h;
}

void Entity::SetSize(UINT16 w, UINT16 h)
{
    SetWidth(w);
    SetHeight(h);
}

INT16 Entity::GetX(void)
{
    return _geometry->x;
}

INT16 Entity::GetY(void)
{
    return _geometry->y;
}

void Entity::SetX(INT16 x)
{
    _geometry->x = x;
}

void Entity::SetY(INT16 y)
{
    _geometry->y = y;
}

void Entity::SetPosition(INT16 x, INT16 y)
{
    SetX(x);
    SetY(y);
}

UINT16 Entity::GetTileW(void)
{
    if (!_tile)
        _tile = new Rect;

    return _tile->w;
}

UINT16 Entity::GetTileH(void)
{
    if (!_tile)
        _tile = new Rect;

    return _tile->h;
}

void Entity::SetTileW(UINT16 w)
{
    if (!_tile)
        _tile = new Rect;
    
    _tile->w = w;
}

void Entity::SetTileH(UINT16 h)
{
    if (!_tile)
        _tile = new Rect;
    
    _tile->h = h;
}

void Entity::SetTileSize(UINT16 w, UINT16 h)
{
    SetTileW(w);
    SetTileH(h);
}

INT16 Entity::GetTileX(void)
{
    if (!_tile)
        _tile = new Rect;
    
    return _tile->x;
}

INT16 Entity::GetTileY(void)
{
    if (!_tile)
        _tile = new Rect;
    
    return _tile->y;
}

void Entity::SetTileX(INT16 x)
{
    if (!_tile)
        _tile = new Rect;
    
    _tile->x = x;
}

void Entity::SetTileY(INT16 y)
{
    if (!_tile)
        _tile = new Rect;
    
    _tile->y = y;
}

void Entity::SetTilePosition(INT16 x, INT16 y)
{
    SetTileX(x);
    SetTileY(y);
}

void Entity::SetTile(Rect tile)
{
    SetTileSize(tile.w, tile.h);
    SetTilePosition(tile.x, tile.y);
}

void Entity::SetTexture(const char* path)
{
    _texture = getTexture(path); // FIXME: one to many texture problem, memory leak
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
            center->x = _center->x - _geometry->x;
            center->y = _center->y - _geometry->y;
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
    delete _tile;
    delete _geometry;
}
