#ifndef INPUT_HPP
#define INPUT_HPP

#include "text.hpp"

class Input final : public Text
{
private:
  uint32_t _time;
  std::string *_ptext;

public:
  Input(std::string *text, FontSize size, SDL_Color color, int x, int y);

  void process(void);

  ~Input();
};

#endif // INPUT_HPP
