#include "geometry.hpp"

#include "SDL.h"
#include "global.hpp"

Rectangle::Rectangle(Rect rect, Color color)
{
    _rect = new Rect;
    SetSize(rect.w, rect.h);
    SetPosition(rect.x, rect.y);

    _color = new Color;
    SetColor(color);
}

void Rectangle::SetW(UINT16 w)
{
    _rect->w = w;
}

void Rectangle::SetH(UINT16 h)
{
    _rect->h = h;
}

void Rectangle::SetSize(UINT16 w, UINT16 h)
{
    SetW(w);
    SetH(h);
}

UINT16 Rectangle::GetW(void)
{
    return _rect->w;
}

UINT16 Rectangle::GetH(void)
{
    return _rect->h;
}

void Rectangle::SetX(INT16 x)
{
    _rect->x = x;
}

void Rectangle::SetY(INT16 y)
{
    _rect->y = y;
}

void Rectangle::SetPosition(INT16 x, INT16 y)
{
    SetX(x);
    SetY(y);
}

INT16 Rectangle::GetX(void)
{
    return _rect->x;
}

INT16 Rectangle::GetY(void)
{
    return _rect->y;
}

void Rectangle::SetColor(Color color)
{
    _color->r = color.r;
    _color->g = color.g;
    _color->b = color.b;
    _color->a = color.a;
}

void Rectangle::Render()
{
    SDL_Rect *rect = new SDL_Rect;
    rect->w = _rect->w;
    rect->h = _rect->h;
    rect->x = _rect->x;
    rect->y = _rect->y;

    SDL_SetRenderDrawColor(global::renderer, _color->r, _color->g, _color->b, _color->a);
    SDL_RenderDrawRect(global::renderer, rect);
    SDL_SetRenderDrawColor(global::renderer, 0, 0, 0, 0);

    delete rect;
}

void Rectangle::RenderFill()
{
    SDL_Rect *rect = new SDL_Rect;
    rect->w = _rect->w;
    rect->h = _rect->h;
    rect->x = _rect->x;
    rect->y = _rect->y;

    SDL_SetRenderDrawColor(global::renderer, _color->r, _color->g, _color->b, _color->a);
    SDL_RenderFillRect(global::renderer, rect);
    SDL_SetRenderDrawColor(global::renderer, 0, 0, 0, 0);

    delete rect;
}

Rectangle::~Rectangle()
{
    delete _rect;
    delete _color;
}