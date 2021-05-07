#ifndef TEXTURE
#define TEXTURE

#include <string>
#include "renderer.hpp"

typedef struct SDL_Rect SDL_Rect;
typedef struct SDL_Texture SDL_Texture;

/*
    Игровая текстура
*/
class Texture final //TODO: попробовать переместить в entity.cpp? (неотдилимые объекты)
{
private:
    SDL_Texture *_texture = nullptr; // Текстура //TODO: shared_ptr?
    SDL_Rect *_tile = nullptr;       // Область текстуры

public:
    /*
        Инициализация текстуры
        SDL_Renderer *renderer - рендер для отрисовки текстуры
        std::string path - путь до файла текстуры
    */
    Texture(Renderer *renderer, std::string path);

    /*
        Инициализация текстуры с заданной областью
        SDL_Renderer *renderer - рендер для отрисовки текстуры
        std::string path - путь до файла текстуры
        int w, h - ширина и высота вырезаемой области текстуры
        int x, y - расположение вырезаемой области текстуры
    */
    Texture(Renderer *renderer, std::string path, int w, int h, int x, int y);

    /*
        Конструктор копирования
    */
    Texture(Texture *texture);

    /*
        Загрузка текстуры
    */
    void loadTexture(Renderer *renderer, std::string path);

    /*
        Изменение размера текстуры
    */
    void setSize(int w, int h);

    /*
        Изменение положения текстуры
    */
    void setPosition(int x, int y);

    friend void Renderer::operator<< (Entity *entity);

    ~Texture();
};

#endif