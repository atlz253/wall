#include "base.hpp"

#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"

Base::Base(int x, SDL_RendererFlip flip) : Unit::Unit()
{
  _hp = 2000;
  _speed = 0;
  _backRange = 0;
  _frontRange = 100;

  if (!textures->key("base")) textures->loadTexture("base", "res/Taiga-Asset-Pack_v2_vnitti/PNG/Props.png");
  _texture = textures->key("base");
  setTile(0, 48, 144, 128);
  _flip = flip;

  setSize(144 * 2, 128 * 2);
  setPosition(x, 270);

  _center = new SDL_Point;
  _center->x = _geometry->x + _geometry->w / 2;
  _center->y = _geometry->y + _geometry->h / 2 + 45;
}

Unit* Base::keyCheck(void)
{
  const Uint8* keysState = events->getKeysState();

  if (!_speed && ((_flip && keysState[SDL_SCANCODE_RIGHTBRACKET]) || (!_flip && keysState[SDL_SCANCODE_Q])))
  {
    _speed = 100;
    return new Knight(getFront(), _flip);
  }
  else
  {
    if (_speed != 0)
      _speed--;
    return nullptr;
  }

  events->eventClear();
}

int Base::getBack(void) { return getFront(); }

int Base::getFront(void)
{
  if (_flip)
    return _center->x - _frontRange;
  else
    return _center->x + _frontRange;
}
