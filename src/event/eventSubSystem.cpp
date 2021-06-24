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
}

bool EventSubSystem::checkEvents(void)
{
  //  Uint32 type;

  while (SDL_PollEvent(_event))
  {
    //    type = _event->type;

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
          case START_EVENT:
            gui->input();
            break;
          case RECORDS_EVENT:
            gui->records();
            break;
          case DEFEAT_EVENT:  // TODO: обрабатывать поражение внутри Base
            int w, h;
            std::string text = "Игрок ";
            Base* base = (Base*)_event->user.data1;
            if (base->getFlip())
              text = text + "1 победил";
            else
              text = text + "2 победил";

            font->getSize(text, FONT_HIGH, &w, &h);
            gui->addEntity(new Entity(font->getTexture(text, FONT_HIGH, {255, 0, 0, 255}), w, h, (SCREEN_WIDTH - w) / 2,
                                      (SCREEN_HEIGHT - h) / 2));
            _action = false;
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
  if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
    return true;
  else
    return false;
}

EventSubSystem::~EventSubSystem() { delete _event; }
