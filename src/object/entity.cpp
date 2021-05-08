#include "print.hpp"
#include "entity.hpp"
#include "texture.hpp"

void Entity::_renderer(SDL_Renderer *renderer)
{
    if (SDL_RenderCopy(renderer, _texture->_texture, _texture->_tile, _geometry))
        printError("SdlWindow: ошибка рендера.", SDL_GetError());
}

Entity::Entity()
{
    printTrace("Entity: создание сущности");
    _geometry = new SDL_Rect;
}

Entity::Entity(Texture *texture)
{
    printWarning("я здесь");
    printTrace("Entity: создание сущности");
    _geometry = new SDL_Rect;
    _texture = texture;
}

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

    _geometry = new SDL_Rect;
    _geometry->h = entity->_geometry->h;
    _geometry->w = entity->_geometry->w;
    _geometry->x = entity->_geometry->x;
    _geometry->y = entity->_geometry->y;

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
