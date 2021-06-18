#include "base.hpp"

#include <iostream>

#include "font.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"

class HealthLine final : public Entity
{
 private:
  SDL_RendererFlip _flip;
  const unsigned short int _HPpoint = BASE_HP / (111 * 3);

 public:
  HealthLine(Base* base) : Entity::Entity()
  {
    _flip = base->getFlip();

    if (!textures->key("healthLine"))
      textures->loadTexture("healthLine", "res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue.png");
    _texture = textures->key("healthLine");
    setTile(13, 68, 111, 6);

    setSize(111 * 3, 6 * 3);

    if (_flip)
      setPosition(SCREEN_WIDTH - 111 * 3, 1 * 3);
    else
      setPosition(0, 1 * 3);
  }

  void process(unsigned short int health)
  {
    if (_flip)
      setPosition(SCREEN_WIDTH - health / _HPpoint, 1 * 3);
    else
      setPosition(health / _HPpoint - 111 * 3, 1 * 3);
  }
};

class HealthBar final : public RotateEntity
{
 private:
  Base* _base;

  HealthLine* _line;

 public:
  HealthBar(Base* base) : RotateEntity::RotateEntity()
  {
    _base = base;
    _flip = base->getFlip();

    _line = new HealthLine(_base);
    gui->addEntity(_line);

    if (!textures->key("healthBar"))
      textures->loadTexture("healthBar", "res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue2.png");
    _texture = textures->key("healthBar");
    setTile(13, 47, 111, 8);

    setSize(111 * 3, 8 * 3);

    if (_flip)
      setPosition(SCREEN_WIDTH - 111 * 3, 0);
    else
      setPosition(0, 0);
  }

  void process(void) override { _line->process(_base->getHealth()); }
};

class MoneyBar final : public Entity
{
 private:
  Base* _base;

 public:
  MoneyBar(Base* base) : Entity::Entity() { _base = base; }

  void process(void) override
  {
    std::string text = std::to_string(_base->getMoney()) + '$';
    _texture = renderText(text, 64, {255, 0, 0, 255});
    setSize(25 * text.length(), 36);

    if (_base->getFlip())
      setPosition(SCREEN_WIDTH - 25 * text.length(), 8 * 3);
    else
      setPosition(0, 8 * 3);
  }
};

Base::Base(int x, SDL_RendererFlip flip) : Unit::Unit()
{
  _money = 300;
  _speed = 0;
  _hp = BASE_HP;
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

  gui->addEntity(new HealthBar(this));
  gui->addEntity(new MoneyBar(this));
}

Unit* Base::keyCheck(void)
{
  const Uint8* keysState = events->getKeysState();

  if (!_speed && _money >= KNIGHT_COST &&
      ((_flip && keysState[SDL_SCANCODE_RIGHTBRACKET]) || (!_flip && keysState[SDL_SCANCODE_Q])))
  {
    _speed = 100;
    _money -= 100;
    return new Knight(getFront(), _flip);
  }
  else
  {
    if (_speed != 0) _speed--;
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

UINT16 Base::getMoney(void) { return _money; }
