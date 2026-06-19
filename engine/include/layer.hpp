#ifndef LAYER
#define LAYER

#include <queue>

class Entity;
class Renderer;

/*
    Слой отрисовки
*/
class Layer
{
protected:
    std::queue<Entity *> *_queue;

public:
    Layer();

    void addEntity(Entity *entity);

    virtual void process(void);

    /*
      Отрисовка элементов слоя
  */
    virtual void renderer(void);

    virtual void clear(void);

    ~Layer();
};

#endif
