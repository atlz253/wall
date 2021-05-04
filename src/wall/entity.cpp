#include "print.hpp"
#include "entity.hpp"
#include "SDL_image.h"

Entity::Entity(SDL_Renderer *renderer, std::string path, int w, int h, int x, int y)
{
    printTrace("Entity: загрузка текстуры", path);
    _rect = new SDL_Rect();
    _renderer = renderer;
    loadTexture(path);
    setSize(w, h);
    setPosition(x, y);
}

void Entity::loadTexture(std::string path)
{
    if (_texture)
        SDL_DestroyTexture(_texture);

    _texture = IMG_LoadTexture(_renderer, path.c_str());

    if (!_texture)
        printError("Entity: не удалось загрузить текстуру.", IMG_GetError());
}

void Entity::setSize(int w, int h)
{
    _rect->w = w;
    _rect->h = h;
}

void Entity::setPosition(int x, int y)
{
    _rect->x = x;
    _rect->y = y;
}

void Entity::renderCopy(void)
{
    if (SDL_RenderCopy(_renderer, _texture, nullptr, _rect))
        printError("SdlWindow: ошибка рендера заднего фона.", SDL_GetError());
}

Entity::~Entity()
{
    printTrace("Entity: удаление текстуры");
    SDL_DestroyTexture(_texture);

    printTrace("Entity: геометрии сущности");
    delete _rect;
}
