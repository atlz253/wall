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
  CLEAR_RECORDS_EVENT,
  DEFEAT_EVENT,
  END_EVENT
};

/*
    Подсистема событий SDL
*/
class EventSubSystem final
{
 private:
  bool _action;

  SDL_Event* _event;

  bool _mouseCheck;
  SDL_Point* _mousePosition;

 public:
  EventSubSystem();

  /*
   * Проверка новых игровых событий
   */
  bool checkEvents(void);

  /*
   * Запущена ли игра?
   */
  bool getAction(void);

  /*
   * Получение текущего события
   */
  SDL_Event* getEvent(void);

  /*
   * Получение позиции мыши
   */
  SDL_Point* getMousePosition(void);

  /*
   * Проверка на левый клик мыши
   */
  bool leftClick(void);

  ~EventSubSystem();
};

#endif  // EVENTS_HPP
