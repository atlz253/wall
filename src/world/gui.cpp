#include "gui.hpp"

Gui::Gui() : Layer::Layer() {}

void Gui::addEntity(Entity *entity) { _queue->push(entity); }

Gui::~Gui() {}
