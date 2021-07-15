#ifndef TEXT
#define TEXT

#include <string>

#include "type.hpp"
#include "entity.hpp"

namespace font
{
  Font *open(std::string path, int size);

  void close(Font *font);
}

class Text : public Entity
{
protected:
  Font *font;
  Color *color;

  std::string text;

  void updateTexture(void);

public:
  Text(std::string text, Font *font, int x = 0, int y = 0);

  void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  int getWidth(void);

  std::string getText(void);

  void getSize(int *w, int *h); // TODO: rewrite

  ~Text();
};

#endif // TEXT
