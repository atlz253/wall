#include "knight.hpp"

#include <iostream>

#include "globals.hpp"
#include "print.hpp"

typedef enum KnightRun
{
  RUN_0 = 32,
  RUN_1 = 128,
  RUN_2 = 224,
  RUN_3 = 320,
  RUN_4 = 416,
  RUN_5 = 512,
  RUN_6 = 608,
  RUN_7 = 704
} KnightRun;

typedef enum KnightAttack
{
  ATTACK_0 = 48,
  ATTACK_1 = 192,
  ATTACK_2 = 336,
  ATTACK_3 = 480,
  ATTACK_4 = 624,
  ATTACK_5 = 768,
  ATTACK_6 = 912,
  ATTACK_7 = 1056,
  ATTACK_8 = 1200,
  ATTACK_9 = 1328,
  ATTACK_10 = 1488,
  ATTACK_11 = 1632,
  ATTACK_12 = 1776,
  ATTACK_13 = 1920,
  ATTACK_14 = 2064,
  ATTACK_15 = 2208,
  ATTACK_16 = 2352,
  ATTACK_17 = 2528,  // FIXME: текстура вылезает за область 48x48
  ATTACK_18 = 2672,
  ATTACK_19 = 2816,
  ATTACK_20 = 2960,
  ATTACK_21 = 3104
} KnightAttack;

int runFrames[8] = {32, 128, 224, 320, 416, 512, 608, 704},
    idleFrames[15] = {16, 80, 144, 208, 272, 336, 400, 464, 528, 592, 656, 720, 784, 848, 912};

Knight::Knight(int x, SDL_RendererFlip flip) : Unit::Unit()
{
  _frame = 0;
  _frameCount = 0;
  _animationSpeed = 5;
  _isRuning = true;

  _hp = 100;
  _speed = 4;
  _backRange = 20;
  _frontRange = 30;

  if (!textures->key("knightRun")) textures->loadTexture("knightRun", "res/Knight/noBKG_KnightRun_strip.png");
  _texture = textures->key("knightRun");

  if (!textures->key("knightAttack")) textures->loadTexture("knightAttack", "res/Knight/noBKG_KnightAttack_strip.png");
  if (!textures->key("knightIdle")) textures->loadTexture("knightIdle", "res/Knight/noBKG_KnightIdle_strip.png");

  setSize(48 * 2, 48 * 2);
  setPosition(x, 441);

  _tile = new SDL_Rect;
  _tile->w = 48;
  _tile->h = 48;
  _tile->x = RUN_0;
  _tile->y = 0;

  _flip = flip;
  _center = new SDL_Point;
  _center->y = _geometry->y + _geometry->h / 2 - 10;
  if (_flip)
    _center->x = _geometry->x + _geometry->w / 2 + 5;
  else
    _center->x = _geometry->x + _geometry->w / 2 - 5;
}

void Knight::process(Unit *next)
{
  Unit::process();
  std::cout << next->getFront() << ' ' << getFront() << std::endl;
  if (next->getFlip() == getFlip() && next->getBack() <= getFront())
  {
    if (_isRuning)
    {
      _isRuning = false;
      _frameCount = 0;
      _frame = 0;
      _texture = textures->key("knightIdle");
      _tile->x = idleFrames[0];
    }
    else if (++_frameCount == _animationSpeed)
    {
      if (++_frame == 15) _frame = 0;

      _tile->x = idleFrames[_frame];

      _frameCount = 0;
    }
  }
  else if ((!_flip && next->getFront() <= getFront()) || (_flip && next->getFront() >= getFront()))
  {
    if (_isRuning)
    {
      _isRuning = false;
      _frameCount = 0;
      _frame = 0;
      _texture = textures->key("knightAttack");
      _tile->x = ATTACK_0;
    }
    else if (++_frameCount == _animationSpeed)
    {
      switch (++_frame)
      {
        case 1:
          _tile->x = ATTACK_1;
          break;
        case 2:
          _tile->x = ATTACK_2;
          break;
        case 3:
          _tile->x = ATTACK_3;
          break;
        case 4:
          _tile->x = ATTACK_4;
          break;
        case 5:
          _tile->x = ATTACK_5;
          break;
        case 6:
          _tile->x = ATTACK_6;
          break;
        case 7:
          _tile->x = ATTACK_7;
          break;
        case 8:
          _tile->x = ATTACK_8;
          break;
        case 9:
          _tile->x = ATTACK_9;
          break;
        case 10:
          _tile->x = ATTACK_10;
          break;
        case 11:
          _tile->x = ATTACK_11;
          break;
        case 12:
          _tile->x = ATTACK_12;
          break;
        case 13:
          _tile->x = ATTACK_13;
          break;
        case 14:
          _tile->x = ATTACK_14;
          break;
        case 15:
          _tile->x = ATTACK_15;
          break;
        case 16:
          _tile->x = ATTACK_16;
          break;
        case 17:
          _tile->x = ATTACK_17;
          break;
        case 18:
          _tile->x = ATTACK_18;
          break;
        case 19:
          _tile->x = ATTACK_19;
          break;
        case 20:
          _tile->x = ATTACK_20;
          break;
        case 21:
          _tile->x = ATTACK_21;
          break;
        default:
          _frame = 0;
          _tile->x = ATTACK_0;
          break;
      }
      _frameCount = 0;
    }
  }
  else
  {
    if (!_isRuning)
    {
      _isRuning = true;
      _frameCount = 0;
      _frame = 0;
      _texture = textures->key("knightRun");
      _tile->x = runFrames[0];
    }
    else if (++_frameCount == _animationSpeed)
    {
      if (++_frame == 8) _frame = 0;

      _tile->x = runFrames[_frame];

      _frameCount = 0;

      if (_flip)
      {
        _geometry->x = _geometry->x - _speed;
        _center->x = _center->x - _speed;
      }
      else
      {
        _geometry->x = _geometry->x + _speed;
        _center->x = _center->x + _speed;
      }
    }
  }
}

int Knight::getBack(void)
{
  if (_flip)
    return _center->x + _backRange;
  else
    return _center->x - _backRange;
}

int Knight::getFront(void)
{
  if (_flip)
    return _center->x - _frontRange;
  else
    return _center->x + _frontRange;
}
