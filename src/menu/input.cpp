#include "input.hpp"

#include <iostream>

#include "globals.hpp"

Input::Input(std::string *text, FontSize size, SDL_Color color, int x, int y) : Text("", size, color, x, y)
{
  SDL_StartTextInput();
  _ptext = text;
  _time = 0;
}

void Input::process()
{
  SDL_Event *event = events->getEvent();

  if (event->type == SDL_TEXTINPUT && _time != event->text.timestamp)
  {
    _time = event->text.timestamp;
    _text += event->text.text;
    *_ptext = _text;
    _updateTexture();
    setPosition((SCREEN_WIDTH - _geometry->w) / 2, _geometry->y);
  }
  else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE && _time != event->key.timestamp &&
           _text.length() > 0)
  {
    _time = event->key.timestamp;
    _text.pop_back();
    *_ptext = _text;
    _updateTexture();
    setPosition((SCREEN_WIDTH - _geometry->w) / 2, _geometry->y);
  }
}

Input::~Input() { SDL_StopTextInput(); }
