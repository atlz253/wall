#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "SDL2/SDL.h"

enum GameEvents
{
  MENU_EVENT,
  RULE_EVENT,
  P1_INPUT_EVENT,
  P2_INPUT_EVENT,
  START_EVENT,
  RECORDS_EVENT,
  DEFEAT_EVENT,
  END_EVENT
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
  bool _mouseCheck;

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
