#include "print.hpp"
#include "entity.hpp"

Entity::Entity(Texture *texture, int w, int h, int x, int y)
{
    printTrace("Entity: создание сущности");
    _geometry = new SDL_Rect;
    _texture = texture;
    setSize(w, h);
    setPosition(x, y);
}

Entity::Entity(Entity *entity)
{
    printTrace("Entity: копирование сущности");
    _geometry = entity->_geometry;
    _texture = entity->_texture;
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

Entity::~Entity()
{
    printTrace("Entity: геометрии сущности");
    delete _geometry;
}
