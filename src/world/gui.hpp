#ifndef GUI_HPP
#define GUI_HPP

#include "layer.hpp"

class Gui final : public Layer
{
 public:
  Gui();

  void addEntity(Entity *entity);

  ~Gui();
};

#endif  // GUI_HPP
