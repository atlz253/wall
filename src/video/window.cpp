#include "window.hpp"

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "globals.hpp"
#include "renderer.hpp"

SDL_Window *_window = nullptr;

Window::Window()
{
  std::cout << "Window: creating window" << std::endl;
  _window = SDL_CreateWindow("wall", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  if (!_window)
  {
    std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Window::freeze(void)
{
  std::cout << "Window: minimized" << std::endl;
  SDL_Event *event = new SDL_Event;

  while (SDL_WaitEvent(event))
    if (event->window.event == SDL_WINDOWEVENT_SHOWN) break;
}

void Window::operator>>(Renderer *renderer)
{
  std::cout << "Window: создание рендера" << std::endl;
  renderer->_renderer =
      SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer->_renderer) std::cout << "Window: не удалось создать рендер:" << SDL_GetError() << std::endl;
}

Window::~Window() { SDL_DestroyWindow(_window); }
