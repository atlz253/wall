#include "eventSubSystem.hpp"

#include <iostream>
#include <string>

#include "base.hpp"
#include "globals.hpp"
#include "print.hpp"

EventSubSystem::EventSubSystem()
{
  _action = true;
  _event = new SDL_Event;
  _mousePosition = new SDL_Point;
  _mouseCheck = false;
}

bool EventSubSystem::checkEvents(void)
{
  while (SDL_PollEvent(_event))
  {
    switch (_event->type)
    {
      case SDL_WINDOWEVENT:
        switch (_event->window.event)
        {
          case SDL_WINDOWEVENT_HIDDEN:
            window->freeze();
            break;
        }
        break;
      case SDL_USEREVENT:
        switch (_event->user.code)
        {
          case MENU_EVENT:
            gui->menu();
            break;
          case RULE_EVENT:
            gui->rules();
            break;
          case CLEAR_RECORDS_EVENT:
            remove("records.bin");
          case RECORDS_EVENT:
            gui->records();
            break;
          case P1_INPUT_EVENT:
            gui->p1_input();
            break;
          case P2_INPUT_EVENT:
            gui->p2_input();
            break;
          case START_EVENT:
            gui->clear();
            action->start();
            break;
          case DEFEAT_EVENT:
            _action = false;
            break;
          case END_EVENT:
            _action = true;
            action->clear();
            gui->menu();
            break;
        }
        break;
      case SDL_QUIT:
        printTrace("SdlWindow: SDL_Quit event");
        return false;
        break;
    }
  }

  return true;
}

bool EventSubSystem::getAction(void) { return _action; }

SDL_Event* EventSubSystem::getEvent(void) { return _event; }

SDL_Point* EventSubSystem::getMousePosition(void)
{
  SDL_GetMouseState(&_mousePosition->x, &_mousePosition->y);
  return _mousePosition;
}

bool EventSubSystem::leftClick(void)
{
  if (!_mouseCheck && (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)))
  {
    _mouseCheck = true;
    return true;
  }
  else
  {
    if (!(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))) _mouseCheck = false;
    return false;
  }
}

EventSubSystem::~EventSubSystem() { delete _event; }
