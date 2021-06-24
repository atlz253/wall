#include "input.hpp"

#include <iostream>

#include "globals.hpp"

Input::Input(FontSize size, SDL_Color color, int x, int y) : Text("", size, color, x, y)
{
  SDL_StartTextInput();
  _time = 0;
}

void Input::process()
{
  SDL_Event *event = events->getEvent();

  if (event->type == SDL_TEXTINPUT && _time != event->text.timestamp)
  {
    _time = event->text.timestamp;
    _text += event->text.text;
    _updateTexture();
  }
  else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE && _time != event->key.timestamp &&
           _text.length() > 0)
  {
    _time = event->key.timestamp;
    _text.pop_back();
    _updateTexture();
  }
}

Input::~Input() { SDL_StopTextInput(); }
