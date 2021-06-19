#include "eventSubSystem.hpp"

#include <iostream>
#include <string>

#include "base.hpp"
#include "font.hpp"
#include "globals.hpp"
#include "print.hpp"

EventSubSystem::EventSubSystem()
{
  _action = true;
  _event = new SDL_Event;
}

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
      case SDL_USEREVENT:
        switch (_event->user.code)
        {
          case DEFEAT_EVENT:
            SDL_Rect* geometry = new SDL_Rect;
            std::string text = "Игрок ";
            Base* base = (Base*)_event->user.data1;
            if (base->getFlip())
              text = text + "1 победил";
            else
              text = text + "2 победил";

            font->getSize(text, FONT_HIGH, geometry);
            gui->addEntity(new Entity(font->getTexture(text, FONT_HIGH, {255, 0, 0, 255}), geometry->w, geometry->h,
                                      (SCREEN_WIDTH - geometry->w) / 2, (SCREEN_HEIGHT - geometry->h) / 2));
            _action = false;
            delete geometry;
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

bool EventSubSystem::getAction(void) { return _action; }

EventSubSystem::~EventSubSystem() { delete _event; }
