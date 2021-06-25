#include "window.hpp"

#include "SDL2/SDL_image.h"
#include "globals.hpp"
#include "print.hpp"
#include "renderer.hpp"

SdlWindow::SdlWindow()
{
  printTrace("SdlWindow: создание окна");
  _window = SDL_CreateWindow("wall", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  if (!_window)
  {
    printError("SdlWindow: не удалось создать окно:", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void SdlWindow::freeze(void)
{
  printTrace("SdlWindow: окно свернуто");
  SDL_Event *event = new SDL_Event;

  while (SDL_WaitEvent(event))
    if (event->window.event == SDL_WINDOWEVENT_SHOWN) break;
}

void SdlWindow::operator>>(Renderer *renderer)
{
  printTrace("SdlWindow: создание рендера");
  renderer->_renderer =
      SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer->_renderer) printError("SdlWindow: не удалось создать рендер:", SDL_GetError());
}

SdlWindow::~SdlWindow() { SDL_DestroyWindow(_window); }
