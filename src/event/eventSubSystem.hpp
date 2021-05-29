#include "SDL2/SDL.h"

/*
    Подсистема обработки событий SDL
*/
class EventSubSystem final
{
 private:
  SDL_Event* _event;  // Обработчик событий
  const Uint8* _keysState;

 public:
  EventSubSystem();

  /*
      Проверка новых игровых событий
  */
  bool checkEvents(void);

  const Uint8* getKeysState(void);

  void eventClear(void);

  ~EventSubSystem();
};
