#ifndef RENDERER
#define RENDERER

#include "window.hpp"

class Entity;

/*
    Объект класса отвечает за рендер кадра
*/
class Renderer final
{
private:
    SDL_Renderer *_renderer = nullptr;

public:
    Renderer();

    /*
        Очистка рендера
    */
    void clear(void);

    /*
        Вывод рендера на экран
    */
    void draw(void);

    /*
        Возвращает стандартное представление рендера SDL
    */
    SDL_Renderer *getRender(void);

    /*
        Операция прорисовки сущности на рендер
    */
    void operator<< (Entity *entity);

    friend void SdlWindow::operator>> (Renderer *renderer);

    ~Renderer();
};

#endif