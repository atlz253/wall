#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include "entity.hpp"
#include "font.hpp"

class Text final : public Entity
{
 private:
  std::string _text;
  FontSize _size;

 public:
  Text(std::string text, FontSize size, SDL_Color color, int x, int y);

  void setColor(SDL_Color color);

  std::string getText(void);

  ~Text();
};

#endif  // TEXT_HPP
