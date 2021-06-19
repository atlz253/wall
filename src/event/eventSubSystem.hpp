#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "SDL2/SDL.h"

enum GameEvents
{
  DEFEAT_EVENT = 0
};

/*
    Подсистема обработки событий SDL
*/
class EventSubSystem final
{
 private:
  bool _action;
  SDL_Event* _event;  // Обработчик событий
  const Uint8* _keysState;

 public:
  EventSubSystem();

  /*
      Проверка новых игровых событий
  */
  bool checkEvents(void);

  const Uint8* getKeysState(void);

  bool getAction(void);

  void eventClear(void);

  ~EventSubSystem();
};

#endif // EVENTS_HPP
