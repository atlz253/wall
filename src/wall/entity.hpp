#ifndef ENTITY
#define ENTITY

#include "SDL.h"
#include <string>

/*
    Игровая сущность
*/
class Entity
{
private:
    SDL_Texture *_texture = nullptr;   // Текстура сущности
    SDL_Rect *_rect = nullptr;         // Геометрия сущности
    SDL_Renderer *_renderer = nullptr; // Рендер, где рисуется сущность
public:
    /*
        Инициализация сущности:
        SDL_Renderer *renderer - рендер для отрисовки сущности
        std::string path - путь до файла текстуры
        int w, h - ширина и высота сущности
        int x, y - расположение сущности
    */
    Entity(SDL_Renderer *renderer, std::string path, int w, int h, int x, int y);

    /*
        Загрузка текстуры
    */
    void loadTexture(std::string path);

    /*
        Изменение размера сущности
    */
    void setSize(int w, int h);

    /*
        Изменение положения сущности
    */
    void setPosition(int x, int y);

    /*
        Копирует текстуру в назначенный рендер
    */
    void renderCopy(void);

    ~Entity();
};

#endif
