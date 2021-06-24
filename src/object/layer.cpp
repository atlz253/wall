#include "layer.hpp"

#include "entity.hpp"
#include "print.hpp"

Layer::Layer() { _queue = new std::queue<Entity *>; }

void Layer::addEntity(Entity *entity) { _queue->push(entity); }

void Layer::process(void) {}

void Layer::renderer(void)
{
  std::queue<Entity *> *_tmp = new std::queue<Entity *>;

  while (!_queue->empty())
  {
    _queue->front()->process();
    _queue->front()->render();
    _tmp->push(_queue->front());
    _queue->pop();
  }

  delete _queue;
  _queue = _tmp;
}

void Layer::clear(void)
{
  while (!_queue->empty())
  {
    delete _queue->front();
    _queue->pop();
  }
}

Layer::~Layer()
{
  clear();
  delete _queue;
}
