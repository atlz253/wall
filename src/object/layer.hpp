#ifndef LAYER
#define LAYER

#include <list>
#include <queue>

class Entity;
class Renderer;

/*
    Слой отрисовки
*/
class Layer  // TODO: свой renderer для слоя
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

  void clear(void);

  ~Layer();
};

#endif
