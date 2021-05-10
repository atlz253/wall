#ifndef LAYER
#define LAYER

#include <list>

class Entity;
class Renderer;

/*
    Слой отрисовки
*/
class Layer
{
protected:
    std::list<Entity *> _list;               // Список используемых текстур
    std::list<Entity *>::iterator _iterator; // Итератор для работы со списком
public:
    Layer();

    /*
        Отрисовка элементов слоя
    */
    virtual void renderer(void);

    ~Layer();
};

#endif