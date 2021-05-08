#include "print.hpp" // убрать потом
#include "sky.hpp"

Sky::Sky(Texture *texture)
{
    printDebug("Sky: инициализация заднего фона");
    _texture = texture;
    _geometry->h = 608;
    _geometry->w = 124;
    _geometry->y = 0;
}

void Sky::_renderer(SDL_Renderer *renderer)
{
    _geometry->x = 0;

    for (int i = 0; i < 11; i ++)
    {
        _geometry->x = i * _geometry->w;
        Entity::_renderer(renderer);
    }
}