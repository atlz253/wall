#ifndef ENTITY
#define ENTITY

#include "texture.hpp"

/*
    Базовая игровая сущность
*/
class Entity
{
private:
    Texture *_texture = nullptr;   // Текстура сущности
    SDL_Rect *_geometry = nullptr; // Геометрия сущности
public:
    /*
        Инициализация сущности:
        Texture texture - текстура сущности
        int w, h - ширина и высота сущности
        int x, y - расположение сущности
    */
    Entity(Texture *texture, int w, int h, int x, int y);

    /*
        Конструктор копирования
        Копия разделяет объект класса Texture с родителем, 
        поэтому обновление текстуры будет проходить для всех копий объекта
    */
    Entity(Entity *entity);

    /*
        Изменение размера сущности
    */
    void setSize(int w, int h);

    /*
        Изменение положения сущности
    */
    void setPosition(int x, int y);

    friend void Renderer::operator<< (Entity *entity);

    ~Entity();
};

#endif
