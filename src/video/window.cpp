#include "window.hpp"

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "globals.hpp"

SDL_Window *sdl_window = nullptr;
SDL_Renderer *renderer = nullptr;

Window::Window()
{
  std::cout << "Creating window" << std::endl;
  sdl_window = SDL_CreateWindow("wall", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (!sdl_window)
  {
    std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
    std::cout << "Failed to create renderer:" << SDL_GetError() << std::endl;
}

void Window::freeze(void)
{
  std::cout << "Window minimize" << std::endl;
  SDL_Event *event = new SDL_Event;

  while (SDL_WaitEvent(event))
    if (event->window.event == SDL_WINDOWEVENT_SHOWN)
      break;
}

void Window::clear(void)
{
  SDL_RenderClear(renderer);
}

void Window::draw(void)
{
  SDL_RenderPresent(renderer);
}

Window::~Window() { SDL_DestroyWindow(sdl_window); }
