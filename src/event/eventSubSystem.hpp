#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "SDL2/SDL.h"

enum GameEvents
{
  MENU_EVENT,
  RULE_EVENT,
  START_EVENT,
  RECORDS_EVENT,
  DEFEAT_EVENT
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
  SDL_Point* _mousePosition;

 public:
  EventSubSystem();

  /*
      Проверка новых игровых событий
  */
  bool checkEvents(void);

  bool getAction(void);

  SDL_Event* getEvent(void);

  SDL_Point* getMousePosition(void);

  bool leftClick(void);

  ~EventSubSystem();
};

#endif  // EVENTS_HPP
