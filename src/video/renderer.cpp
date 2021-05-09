#include "print.hpp"
#include "entity.hpp"
#include "renderer.hpp"

Renderer::Renderer()
{
}

void Renderer::clear(void)
{
    SDL_RenderClear(_renderer);
}

void Renderer::draw(void) 
{
    SDL_RenderPresent(_renderer);
}

SDL_Renderer *Renderer::getRender(void)
{
    return _renderer;
}

void Renderer::operator<< (Entity *entity)
{
    entity->_renderer(_renderer, entity->_texture, entity->_geometry);
}