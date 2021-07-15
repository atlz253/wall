#include "base.hpp"

#include <fstream>
#include <iostream>

#include "globals.hpp"
#include "knight.hpp"
#include "random.hpp"
#include "interface.hpp"
#include "keyboard.hpp"

class HealthLine final : public Entity
{
private:
  Flip _flip;
  const unsigned short int _HPpoint = BASE_HP / (111 * 3);

public:
  HealthLine(Base *base) : Entity::Entity()
  {
    _flip = base->getFlip();

    _texture = getTexture("res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue.png");
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

class HealthBar final : public Entity
{
private:
  Base *_base;

  HealthLine *_line;

public:
  HealthBar(Base *base) : Entity()
  {
    _base = base;
    _flip = base->getFlip();

    _line = new HealthLine(_base);
    gui->addEntity(_line);

    _texture = getTexture("res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue2.png");
    setTile(13, 47, 111, 8);

    setSize(111 * 3, 8 * 3);

    if (_flip)
      setPosition(SCREEN_WIDTH - 111 * 3, 0);
    else
      setPosition(0, 0);
  }

  void process(void) override { _line->process(_base->getHealth()); }
};

// class MoneyBar final : public Entity // FIXME: Text inheritance
// {
// private:
//   Base *_base;

// public:
//   MoneyBar(Base *base) : Entity::Entity() { _base = base; }

//   void process(void) override
//   {
//     std::string text = std::to_string(_base->getMoney()) + '$';
//     SDL_DestroyTexture(_texture);
//     _texture = engine::font->getTexture(text, FONT_MEDIUM, {255, 0, 0, 255});
//     engine::font->getSize(text, FONT_MEDIUM, &_geometry->w, &_geometry->h);

//     if (_base->getFlip())
//       setPosition(SCREEN_WIDTH - _geometry->w, _geometry->h);
//     else
//       setPosition(0, _geometry->h);
//   }
// };

void Base::_defeat(void)
{
  int w, h;
  std::string text = "Игрок ";
  struct record *rec = new record, *tmp = new record;
  std::ifstream ifile("records.bin", std::ios::binary);
  std::ofstream ofile("_tmp", std::ios::binary | std::ios::app);

  rec->score = getCount() * 50 + _money;
  clearCount();

  if (ifile.is_open())
  {
    int n = 0;
    bool isWritten = false;

    while (n < 9)
    {
      ifile.read((char *)&tmp->score, sizeof(tmp->score));

      size_t tlength;
      ifile.read((char *)&tlength, sizeof(tlength));
      char *buf = new char[tlength];
      ifile.read(buf, tlength);
      tmp->name = buf;
      delete[] buf;

      std::cout << tmp->score << " " << rec->score << std::endl;

      if (ifile.eof())
      {
        break;
      }
      else if (!isWritten && ((tmp->score < rec->score) || (ifile.eof() && n < 9)))
      {
        ofile.write((char *)&rec->score, sizeof(rec->score));
        if (getFlip())
        {
          size_t length = 1;
          ofile.write((char *)&length, sizeof(length));
          ofile.write((char *)"", length);
        }
        else
        {
          size_t length = 1;
          ofile.write((char *)&length, sizeof(length));
          ofile.write((char *)"", length);
        }

        isWritten = true;
        n++;
      }

      if (n < 9)
      {
        ofile.write((char *)&tmp->score, sizeof(tmp->score));
        ofile.write((char *)&tlength, sizeof(tlength));
        ofile.write((char *)tmp->name.c_str(), tlength);

        n++;
      }
    }
  }
  else
  {
    std::cout << "creater record.bin" << std::endl;

    ofile.write((char *)&rec->score, sizeof(rec->score));
    if (getFlip())
    {
      size_t length = 1;
      ofile.write((char *)&length, sizeof(length));
      ofile.write((char *)"", length);
    }
    else
    {
      size_t length = 1;
      ofile.write((char *)&length, sizeof(length));
      ofile.write((char *)"", length);
    }
  }

  text += " победил";

  Font *fontt = font::open("res/joystix_monospace.ttf", 26);
  Text *textt = new Text(text, fontt);
  textt->getSize(&w, &h);
  textt->setPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - 200);
  gui->addEntity(textt);

  text = "счет: " + std::to_string(rec->score);
  textt = new Text(text, fontt);
  textt->getSize(&w, &h);
  textt->setPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - 100);
  gui->addEntity(textt);

  gui->addEntity(new Button("в меню", fontt, 150, 30, (SCREEN_WIDTH - 150) / 2,
                            (SCREEN_HEIGHT - 30) / 2 + 30, []()
                            {
                              action->clear();
                              gui->menu();
                            }));

  rename("_tmp", "records.bin");
  ofile.close();
  ifile.close();
}

Base::Base(int x, Flip flip) : Unit::Unit()
{
  _money = 300;
  _speed = 0;
  _hp = BASE_HP;
  _frontRange = 30;
  _earnSpeed = 0;

  _texture = getTexture("res/Taiga-Asset-Pack_v2_vnitti/PNG/Props.png");
  setTile(0, 48, 144, 128);
  _flip = flip;

  setSize(144 * 2, 128 * 2);
  setPosition(x, 270);

  _center = new Point;
  if (_flip)
    _center->x = _geometry->x + _geometry->w / 2 - 60;
  else
    _center->x = _geometry->x + _geometry->w / 2 + 60;
  _center->y = _geometry->y + _geometry->h / 2 + 45;

  gui->addEntity(new HealthBar(this));
  // gui->addEntity(new MoneyBar(this));
}

Unit *Base::keyCheck(void)
{
  keys state = keyboard::state(nullptr);

  if (!_speed && _money >= KNIGHT_COST &&
      ((_flip && state[SCANCODE_RIGHTBRACKET]) || (!_flip && state[SCANCODE_Q])))
  {
    _speed = 100;
    _money -= 100;
    return new Knight(getBack(), _flip);
  }
  else
  {
    if (_speed != 0)
      _speed--;
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

uint16_t Base::getMoney(void) { return _money; }

void Base::addMoney(uint16_t money) { _money += money; }

void Base::setDamage(uint16_t damage)
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