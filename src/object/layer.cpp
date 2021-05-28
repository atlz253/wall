#include "layer.hpp"

#include "entity.hpp"
#include "print.hpp"

Layer::Layer() {}

void Layer::renderer(void)
{
  for (_iterator = _list.begin(); _iterator != _list.end(); _iterator++)
  {
    (*_iterator)->process();
    (*_iterator)->renderer();
  }
}

Layer::~Layer()
{
  for (_iterator = _list.begin(); _iterator != _list.end(); _iterator++) delete *_iterator;
}
