#ifndef GUI_HPP
#define GUI_HPP

#include "layer.hpp"

class Gui final : public Layer
{
 public:
  Gui();

  void menu(void);

  void rules(void);

  void records(void);

  void input(void);

  ~Gui();
};

#endif  // GUI_HPP
