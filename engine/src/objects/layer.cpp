#include "layer.hpp"

#include <iostream>

#include "entity.hpp"

std::queue<Entity *> *tmpq = nullptr;

Layer::Layer() { _queue = new std::queue<Entity *>; }

void Layer::addEntity(Entity *entity) { _queue->push(entity); }

void Layer::process(void) {}

void Layer::renderer(void)
{
  tmpq = new std::queue<Entity *>;

  while (!_queue->empty())
  {
    _queue->front()->process();

    if (!_queue->empty())
    {
      _queue->front()->render();
      tmpq->push(_queue->front());
      _queue->pop();
    }
  }

  delete _queue;
  _queue = tmpq;
  tmpq = nullptr;
}

void Layer::clear(void)
{
  while (!_queue->empty())
  {
    delete _queue->front();
    _queue->pop();
  }

  while (tmpq && !tmpq->empty())
  {
    delete tmpq->front();
    tmpq->pop();
  }
}

Layer::~Layer()
{
  clear();
  delete _queue;
}
