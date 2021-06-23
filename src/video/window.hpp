#ifndef SDLWINDOW
#define SDLWINDOW

#include "SDL2/SDL.h"

class Renderer;

/*
    Объект класса содержит окно, созданное средствами SDL2
*/
class SdlWindow final
{
 private:
  const int _SCREEN_WIDTH = 1280;  // TODO: переместить в globals.cpp
  const int _SCREEN_HEIGHT = 720;

  SDL_Window *_window = nullptr;  // Основное окно игры

 public:
  /*
      Инициализация окна
  */
  SdlWindow();

  void freeze(void);

  /*
      Операция содания рендера
  */
  void operator>>(Renderer *renderer);

  ~SdlWindow();
};

#endif
