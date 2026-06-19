#ifndef GUI_HPP
#define GUI_HPP

#include "layer.hpp"

class Button;

class Gui final : public Layer
{
private:
  Button *_buttons[4];
  int _buttonsCount;
  int _selectedButton;

  void addButton(Button *button);

  void processInput(void);

public:
  Gui();

  void renderer(void) override;

  void menu(void);

  void rules(void);

  void records(void);

  ~Gui();
};

#endif // GUI_HPP
