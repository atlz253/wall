#include "knight.hpp"

#include <iostream>
#include <string>

#include "globals.hpp"
#include "random.hpp"

const int runFrames[8] = {32, 128, 224, 320, 416, 512, 608, 704},
          attackFrames[22] = {48, 192, 336, 480, 624, 768, 912, 1056, 1200, 1328, 1488,
                              1632, 1776, 1920, 2064, 2208, 2352, 2528, 2672, 2816, 2960, 3104},
          idleFrames[15] = {16, 80, 144, 208, 272, 336, 400, 464, 528, 592, 656, 720, 784, 848, 912},
          deathFrames[15] = {32, 128, 224, 320, 416, 512, 608, 704, 800, 896, 992, 1088, 1184, 1280, 1376};

const std::string knightRun = "res/Knight/noBKG_KnightRun_strip.png",
                  knightAttack = "res/Knight/noBKG_KnightAttack_strip.png",
                  knightIdle = "res/Knight/noBKG_KnightIdle_strip.png",
                  knightDeath = "res/Knight/noBKG_KnightDeath_strip.png";

Knight::Knight(int x, Flip flip) : Unit::Unit()
{
  _frame = 0;
  _frameCount = 0;
  _animationSpeed = 5;
  _isRuning = true;

  _hp = 100;
  _speed = 4;
  _damage = 30;
  _backRange = 20;
  _frontRange = 30;

  _texture = getTexture(knightRun);

  SetSize(48 * 2, 48 * 2);

  if (_flip)
    SetPosition(x + 48, 441);
  else
    SetPosition(x - 48, 441);

  _tile = new Rect;
  _tile->w = 48;
  _tile->h = 48;
  _tile->x = runFrames[0];
  _tile->y = 0;

  _flip = flip;
  _center = new Point;
  _center->y = _geometry->y + _geometry->h / 2 - 10;
  if (_flip)
    _center->x = _geometry->x + _geometry->w / 2 + 5;
  else
    _center->x = _geometry->x + _geometry->w / 2 - 5;
}

void Knight::process(Unit *next)
{
  Unit::process();

  if (!_hp)
  {
    if (_texture != getTexture(knightDeath))
    {
      _isRuning = false;
      _frameCount = 0;
      _frame = 0;
      _texture = getTexture(knightDeath);
      _tile->x = deathFrames[0];
    }
    else if (++_frameCount == _animationSpeed && _frame < 14)
    {
      _tile->x = deathFrames[++_frame];
      _frameCount = 0;
    }
  }
  else if (_flip == next->getFlip() &&
           ((!_flip && next->getBack() <= getFront()) || (_flip && next->getBack() >= getFront())))
  {
    if (_isRuning)
    {
      _isRuning = false;
      _frameCount = 0;
      _frame = 0;
      _texture = getTexture(knightIdle);
      _tile->x = idleFrames[0];
    }
    else if (++_frameCount == _animationSpeed)
    {
      if (++_frame == 15)
        _frame = 0;

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
      _texture = getTexture(knightAttack);
      _tile->x = attackFrames[0];
    }
    else if (++_frameCount == _animationSpeed)
    {
      if (++_frame == 22)
      {
        _frame = 0;
        if (_hp > _damage)
          next->setDamage(random(_damage, _hp));
        else
          next->setDamage(_damage);
      }

      _tile->x = attackFrames[_frame];

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
      _texture = getTexture(knightRun);
      _tile->x = runFrames[0];
    }
    else if (++_frameCount == _animationSpeed)
    {
      if (++_frame == 8)
        _frame = 0;

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

uint16_t Knight::getReward(void) { return random(0, KNIGHT_COST + 25); }
