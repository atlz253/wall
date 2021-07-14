#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "entity.hpp"

const Uint8 BUTTON_WIDTH = 150;
const Uint8 BUTTON_HEIGHT = 30;

class Text;
typedef struct _TTF_Font Font;

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
