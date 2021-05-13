#include "print.hpp"
#include "entity.hpp"

RotateEntity::RotateEntity(Entity *&entity, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX, int tileY, SDL_RendererFlip flip) : Entity::Entity(entity, entityW, entityH, entityX, entityY, tileW, tileH, tileX, tileY)
{
    _flip = flip;
}

void RotateEntity::renderer(void)
{
    if (SDL_RenderCopyEx(_texture->renderer, _texture, _tile, _geometry, _angle, _center, _flip))
        printError("SdlWindow: ошибка рендера.", SDL_GetError());
}

void RotateEntity::setAngle(const double angle)
{
    _angle = angle;
}

void RotateEntity::setCenter(const int x, const int y)
{
    if (!_center)
        _center = new SDL_Point;

    _center->x = x;
    _center->y = y;
}

void RotateEntity::setFlip(const SDL_RendererFlip flip)
{
    _flip = flip;
}