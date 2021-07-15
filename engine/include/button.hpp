#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "type.hpp"
#include "entity.hpp"

const uint8_t BUTTON_WIDTH = 150;
const uint8_t BUTTON_HEIGHT = 30;

class Text;

class Button final : public Entity
{
private:
  Text *_text;
  void (*event)(void);

public:
  Button(std::string text, Font *font, int x, int y, void (*event)(void));

  void process(void) override;

  void render(void) override;

  ~Button();
};

#endif // BUTTON_HPP
