#include "background.hpp"
#include "texture.hpp"
#include "textureManager.hpp"
#include <iostream>

Background::Background(TextureManager *&textures, Renderer *&renderer)
{
    textures->key("sky") = new Texture(renderer, "res/Magic-Cliffs-Environment/PNG/sky.png");
    textures->key("sea") = new Texture(renderer, "res/Magic-Cliffs-Environment/PNG/sea.png");
    textures->key("clouds") = new Texture(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png");

    _texture = textures->key("sky");
    _geometry->h = 608;
    _geometry->w = 124;
    _geometry->y = 0;

    _seaTexture = textures->key("sea");
    _seaGeometry = new SDL_Rect;
    _seaGeometry->h = 192;
    _seaGeometry->w = 124;
    _seaGeometry->y = _geometry->h;

    _cloudsTexture = textures->key("clouds");
    _cloudsGeometry = new SDL_Rect;
    _cloudsGeometry->h = 472;
    _cloudsGeometry->w = 1088;
    _cloudsGeometry->y = 136;
    _cloudsGeometry->x = 0;
}

void Background::_renderer(SDL_Renderer *renderer, Texture *texture, SDL_Rect *geometry)
{
    _geometry->x = 0;
    _seaGeometry->x = 0;

    for (int i = 0; i < 11; i++)
    {
        _geometry->x = i * _geometry->w;
        _seaGeometry->x = i * _seaGeometry->w;

        Entity::_renderer(renderer, _texture, _geometry);
        Entity::_renderer(renderer, _seaTexture, _seaGeometry);
    }

    _cloudsAnimation += 1;

    if (_cloudsAnimation > 0)
    {
        _cloudsGeometry->x = _cloudsAnimation - 1088;
        Entity::_renderer(renderer, _cloudsTexture, _cloudsGeometry);
    }

    _cloudsGeometry->x = 0 + _cloudsAnimation;
    Entity::_renderer(renderer, _cloudsTexture, _cloudsGeometry);

    if (_cloudsAnimation < 192)
    {
        _cloudsGeometry->x = 1088 + _cloudsAnimation;
        Entity::_renderer(renderer, _cloudsTexture, _cloudsGeometry);
    }
    else if (_cloudsAnimation == 1088)
    {
        _cloudsAnimation = 0;
    }
}