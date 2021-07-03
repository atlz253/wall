#ifndef RENDERER
#define RENDERER

#include "window.hpp"

typedef struct SDL_Renderer SDL_Renderer;

class Entity;

/*
    Объект класса отвечает за рендер кадра
*/
class Renderer final
{
 private:
  SDL_Renderer *_renderer = nullptr;

 public:
  Renderer();

  /*
      Очистка рендера
  */
  void clear(void);

  /*
      Вывод рендера на экран
  */
  void draw(void);

  /*
      Возвращает стандартное представление рендера SDL
  */
  SDL_Renderer *getRender(void);

  friend void Window::operator>>(Renderer *renderer);

  ~Renderer();
};

#endif
