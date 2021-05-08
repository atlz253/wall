#include "print.hpp"
#include "texture.hpp"
#include "SDL_image.h"
#include "renderer.hpp"

Texture::Texture(Renderer *renderer, std::string path)
{
    printTrace("Texture: инициализация текстуры");
    loadTexture(renderer, path);
}

Texture::Texture(Renderer *renderer, std::string path, int w, int h, int x, int y)
{
    printTrace("Texture: инициализация текстуры");
    loadTexture(renderer, path);
    setSize(w, h);
    setPosition(x, y);
}

Texture::Texture(Texture *texture)
{
    printTrace("Texture: копирование текстуры");
    _texture = texture->_texture;

    _tile = new SDL_Rect;
    setSize(
        texture->_tile->w, 
        texture->_tile->h);
    setPosition(
        texture->_tile->x, 
        texture->_tile->y);
}

void Texture::loadTexture(Renderer *renderer, std::string path)
{
    printTrace("Texture: загрузка текстуры", path);
    if (_texture)
        SDL_DestroyTexture(_texture);

    _texture = IMG_LoadTexture(renderer->getRender(), path.c_str());

    if (!_texture)
        printError("Texture: не удалось загрузить текстуру.", IMG_GetError());
}

void Texture::setSize(int w, int h)
{
    if (!_tile)
    {
        _tile = new SDL_Rect;
        _tile->x = 0;
        _tile->y = 0;
    }

    _tile->w = w;
    _tile->h = h;
}

void Texture::setPosition(int x, int y)
{
    if (!_tile)
    {
        _tile = new SDL_Rect;
        _tile->w = 64;
        _tile->h = 64;
    }

    _tile->x = x;
    _tile->y = y;
}

Texture::~Texture()
{
    printTrace("Texture: удаление текстуры");
    SDL_DestroyTexture(_texture);
}