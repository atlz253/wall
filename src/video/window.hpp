#ifndef SDLWINDOW
#define SDLWINDOW

class Renderer;

class Window final
{
 public:
  Window();

  void freeze(void);

  /*
      Операция содания рендера
  */
  void operator>>(Renderer *renderer); // TODO: remove

  ~Window();
};

#endif
