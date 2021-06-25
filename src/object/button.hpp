#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "entity.hpp"
#include "globals.hpp"

const Uint8 BUTTON_WIDTH = 150;  // TODO: использовать типы из SDL
const Uint8 BUTTON_HEIGHT = 30;

class Text;

class Button final : public Entity
{
 private:
  Text *_text;
  SDL_Event *_event;

 public:
  Button(std::string text, int x, int y);

  Button(std::string text, int x, int y, SDL_Event *event);

  void bindEvent(SDL_Event *event);

  void process(void) override;

  void render(void) override;
};

#endif  // BUTTON_HPP
