#include "eventSubSystem.hpp"

#include <iostream>

#include "print.hpp"

EventSubSystem::EventSubSystem() { _event = new SDL_Event; }

bool EventSubSystem::checkEvents(void)
{
  while (SDL_PollEvent(_event))
  {
    _keysState = SDL_GetKeyboardState(nullptr);

    switch (_event->type)
    {
      case SDL_WINDOWEVENT:
        switch (_event->window.event)
        {
          case SDL_WINDOWEVENT_HIDDEN:
            printTrace("SdlWindow: окно свернуто");
            while (SDL_WaitEvent(_event))
              if (_event->window.event == SDL_WINDOWEVENT_SHOWN) break;
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

const Uint8* EventSubSystem::getKeysState(void) { return _keysState; }

EventSubSystem::~EventSubSystem() { delete _event; }
