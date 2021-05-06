#include "renderer.hpp"
#include "entity.hpp"
#include "print.hpp"

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
    if (SDL_RenderCopy(_renderer, entity->_texture->_texture, entity->_texture->_tile, entity->_geometry))
        printError("SdlWindow: ошибка рендера.", SDL_GetError());
}