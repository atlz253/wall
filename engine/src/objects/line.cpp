#include "geometry.hpp"

#include "SDL.h"
#include "global.hpp"

#include <iostream>

Line::Line(Point start, Point end, Color color)
{
    _start = new Point;
    SetStart(start);

    _end = new Point;
    SetEnd(end);
    
    _color = new Color;
    SetColor(color);
}

void Line::SetStart(Point start)
{
    _start->x = start.x;
    _start->y = start.y;
}

void Line::SetEnd(Point end)
{
    _end->x = end.x;
    _end->y = end.y;
}

void Line::SetColor(Color color)
{
    _color->r = color.r;
    _color->g = color.g;
    _color->b = color.b;
    _color->a = color.a;
}

void Line::Render(void)
{
    SDL_SetRenderDrawColor(global::renderer, _color->r, _color->g, _color->b, _color->a);
    SDL_RenderDrawLine(global::renderer, _start->x, _start->y, _end->x, _end->y);
    SDL_SetRenderDrawColor(global::renderer, 0, 0, 0, 0);
}

Line::~Line()
{
    delete _end;
    delete _start;
    
    delete _color;
}