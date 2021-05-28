#include "window.hpp"

#include "SDL2/SDL_image.h"
#include "print.hpp"
#include "renderer.hpp"

SdlWindow::SdlWindow()
{
  printTrace("SdlWindow: создание окна");
  _window = SDL_CreateWindow("wall", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, _SCREEN_WIDTH,
                             _SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  if (!_window)
  {
    printError("SdlWindow: не удалось создать окно:", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void SdlWindow::operator>>(Renderer *renderer)
{
  printTrace("SdlWindow: создание рендера");
  renderer->_renderer =
      SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  // TODO: время кадра

  if (!renderer->_renderer) printError("SdlWindow: не удалось создать рендер:", SDL_GetError());
}

SdlWindow::~SdlWindow() { SDL_DestroyWindow(_window); }
