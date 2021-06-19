#ifndef FONT_HPP
#define FONT_HPP

#include <string>

#include "entity.hpp"

enum FontSize
{
  FONT_HIGH = 48,
  FONT_MEDIUM = 26,
  FONT_LOW = 36
};

typedef struct _TTF_Font TTF_Font;
typedef struct SDL_Color SDL_Color;
typedef struct SDL_Texture SDL_Texture;

class Font final
{
 private:
  TTF_Font *_fontHigh;
  TTF_Font *_fontMedium;
  TTF_Font *_fontLow;

  TTF_Font *_getFont(FontSize size);
 public:
  Font();

  void open(std::string path);

  SDL_Texture *getTexture(std::string text, FontSize size, SDL_Color color);

  void getSize(std::string text, FontSize size, SDL_Rect *geometry);

  ~Font();
};

#endif  // FONT_HPP
