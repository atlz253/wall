#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include "entity.hpp"
#include "font.hpp"

class Text : public Entity
{
 protected:
  std::string _text;
  FontSize _size;
  SDL_Color _color;

  void _updateTexture(void);

 public:
  Text(std::string text, FontSize size, SDL_Color color, int x, int y);

  void setColor(SDL_Color color);

  int getWidth(void);

  std::string getText(void);

  ~Text();
};

#endif  // TEXT_HPP
