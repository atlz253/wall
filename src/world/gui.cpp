#include "gui.hpp"

Gui::Gui() : Layer::Layer() {}

void Gui::addEntity(Entity *entity) { _list.push_back(entity); }
