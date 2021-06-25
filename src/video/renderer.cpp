#include "renderer.hpp"

#include "entity.hpp"
#include "print.hpp"

Renderer::Renderer() {}

void Renderer::clear(void) { SDL_RenderClear(_renderer); }

void Renderer::draw(void) { SDL_RenderPresent(_renderer); }

SDL_Renderer *Renderer::getRender(void) { return _renderer; }

Renderer::~Renderer() { SDL_DestroyRenderer(_renderer); }
