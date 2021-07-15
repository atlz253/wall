#ifndef INTERFACE
#define INTERFACE

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

  void getSize(int *w, int *h);

  ~Text();
};

class Button final : public Entity
{
private:
  Text *_text;
  void (*event)(void);

public:
  Button(std::string text, Font *font, int w, int h, int x = 0, int y = 0, void (*event)(void) = nullptr);

  void process(void) override;

  void render(void) override;

  ~Button();
};

#endif // INTERFACE