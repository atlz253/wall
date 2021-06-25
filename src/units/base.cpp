#include "base.hpp"

#include <fstream>
#include <iostream>

#include "button.hpp"
#include "font.hpp"
#include "globals.hpp"
#include "knight.hpp"
#include "print.hpp"
#include "random.hpp"

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
    SDL_DestroyTexture(_texture);
    _texture = font->getTexture(text, FONT_MEDIUM, {255, 0, 0, 255});
    font->getSize(text, FONT_MEDIUM, &_geometry->w, &_geometry->h);

    if (_base->getFlip())
      setPosition(SCREEN_WIDTH - _geometry->w, _geometry->h);
    else
      setPosition(0, _geometry->h);
  }
};

void Base::_defeat(void)
{
  int w, h;
  std::string text = "Игрок ";
  SDL_Event* event;
  struct record* rec = new record;
  std::ofstream file("records.bin", std::ios::binary | std::ios::app);

  rec->score = getCount() * 50 + _money;
  file.write((char*)&rec->score, sizeof(rec->score));

  if (getFlip())
  {
    size_t length = p1->length() + 1;
    file.write((char*)&length, sizeof(length));
    file.write((char*)p1->c_str(), length);

    text = text + *p1;
  }
  else
  {
    size_t length = p2->length() + 1;
    file.write((char*)&length, sizeof(length));
    file.write((char*)p2->c_str(), length);

    text = text + *p2;
  }
  text += " победил";

  font->getSize(text, FONT_MEDIUM, &w, &h);
  gui->addEntity(new Text(text, FONT_MEDIUM, {255, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - 200));

  text = "счет: " + std::to_string(rec->score);
  font->getSize(text, FONT_MEDIUM, &w, &h);
  gui->addEntity(new Text(text, FONT_MEDIUM, {255, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - 100));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = END_EVENT;
  gui->addEntity(new Button("в меню", (SCREEN_WIDTH - BUTTON_WIDTH) / 2,
                            (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT, event));

  file.close();
}

Base::Base(int x, SDL_RendererFlip flip) : Unit::Unit()
{
  _money = 300;
  _speed = 0;
  _hp = BASE_HP;
  _frontRange = 30;
  _earnSpeed = 0;

  if (!textures->key("base")) textures->loadTexture("base", "res/Taiga-Asset-Pack_v2_vnitti/PNG/Props.png");
  _texture = textures->key("base");
  setTile(0, 48, 144, 128);
  _flip = flip;

  setSize(144 * 2, 128 * 2);
  setPosition(x, 270);

  _center = new SDL_Point;
  if (_flip)
    _center->x = _geometry->x + _geometry->w / 2 - 60;
  else
    _center->x = _geometry->x + _geometry->w / 2 + 60;
  _center->y = _geometry->y + _geometry->h / 2 + 45;

  gui->addEntity(new HealthBar(this));
  gui->addEntity(new MoneyBar(this));
}

Unit* Base::keyCheck(void)
{
  const Uint8* keysState = SDL_GetKeyboardState(nullptr);

  if (!_speed && _money >= KNIGHT_COST &&
      ((_flip && keysState[SDL_SCANCODE_RIGHTBRACKET]) || (!_flip && keysState[SDL_SCANCODE_Q])))
  {
    _speed = 100;
    _money -= 100;
    return new Knight(getBack(), _flip);
  }
  else
  {
    if (_speed != 0) _speed--;
    return nullptr;
  }
}

int Base::getBack(void) { return _center->x; }

int Base::getFront(void)
{
  if (_flip)
    return _center->x - _frontRange;
  else
    return _center->x + _frontRange;
}

UINT16 Base::getMoney(void) { return _money; }

void Base::addMoney(UINT16 money) { _money += money; }

void Base::setDamage(UINT16 damage)
{
  if (!_hp)
  {
    return;
  }
  else
  {
    if (_hp >= damage)
      _hp -= damage;
    else
      _hp = 0;

    if (_hp <= 0)
    {
      SDL_Event* defeat = new SDL_Event;
      defeat->type = SDL_USEREVENT;
      defeat->user.code = DEFEAT_EVENT;
      defeat->user.data1 = this;
      SDL_PushEvent(defeat);
      _defeat();
    }
  }
}

void Base::process(void)
{
  Unit::process();

  if (++_earnSpeed >= 50 + _hp / 20)
  {
    _earnSpeed = 0;
    addMoney(random(1, 20 - _hp / 220));
  }
}
