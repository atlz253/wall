#ifndef ENTITY
#define ENTITY

#include "renderer.hpp"

class Texture;

/*
    Базовая игровая сущность
*/
class Entity
{
protected:
    Texture *_texture = nullptr;   // Текстура сущности
    SDL_Rect *_geometry = nullptr; // Геометрия сущности

    /*
        Прорисовка сущности
    */
    virtual void _renderer(SDL_Renderer *renderer, Texture *texture, SDL_Rect *geometry);

public:
    Entity();

    /*
        Инициализация сущности:
        Texture texture - текстура сущности
        int w, h - ширина и высота сущности
        int x, y - расположение сущности
    */
    Entity(Texture *texture, int w, int h, int x, int y);

    /*
        Конструктор копирования
    */
    Entity(Entity *entity);

    /*
        Изменение размера сущности
        int w, h - ширина и высота сущности
    */
    void setSize(int w, int h);

    /*
        Изменение положения сущности
        int x, y - расположение сущности
    */
    void setPosition(int x, int y);

    friend void Renderer::operator<<(Entity *entity);

    ~Entity();
};

#endif
