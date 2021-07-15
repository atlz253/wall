#include "gui.hpp"

#include <fstream>
#include <iostream>

#include "globals.hpp"
#include "interface.hpp"
#include "event.hpp"

#include "base.hpp"

static const int X = (SCREEN_WIDTH - 150) / 2;
static const int Y = (SCREEN_HEIGHT - 30) / 2;

Gui::Gui() : Layer() {}

void Gui::menu(void)
{
  clear();

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  addEntity(new Button("играть", fontt, 150, 30, X, Y - 30 * 4, []()
                       {
                         gui->clear();
                         action->start();
                       }));

  addEntity(new Button("рекорды", fontt, 150, 30, X, Y - 30 * 3, []()
                       { gui->records(); }));

  addEntity(new Button("правила", fontt, 150, 30, X, Y - 30 * 2, []()
                       { gui->rules(); }));

  addEntity(new Button("выход", fontt, 150, 30, X, Y - 30, []()
                       { events::quit(); }));
}

void Gui::rules(void)
{
  int w, h;
  std::string text[3] = {"Бросьте вызов своему противнику и одолейте его в честной схватке!",
                         "Вызывайте своих доблестных бойцов клавишами Q для левого игрока и ",
                         "клавишу } для правого. Победитель получит все!"};

  clear();

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  Text *textt = new Text(text[0], fontt);
  textt->getSize(&w, &h);
  textt->setPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h * 2);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  textt = new Text(text[1], fontt);
  textt->getSize(&w, &h);
  textt->setPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h * 1);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  textt = new Text(text[2], fontt);
  textt->getSize(&w, &h);
  textt->setPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  addEntity(new Button("назад", fontt, 150, 30, X, (SCREEN_HEIGHT - h) / 2 + 30, []()
                       { gui->menu(); }));
}

void Gui::records(void)
{
  record *rec = new record;
  std::string text;
  std::ifstream file("records.bin", std::ios::binary);

  clear();

  if (file.is_open())
  {
    int n = 5, w, h;

    while (true)
    {
      file.read((char *)&rec->score, sizeof(rec->score));
      if (file.eof())
        break;

      size_t length;
      file.read((char *)&length, sizeof(length));
      char *buf = new char[length];
      file.read(buf, length);
      rec->name = buf;
      delete[] buf;

      text = rec->name + " " + std::to_string(rec->score);

      Font *fontt = font::open("res/joystix_monospace.ttf", 20);

      Text *textt = new Text(text, fontt);
      textt->getSize(&w, &h);
      textt->setPosition((SCREEN_WIDTH - w) / 2, h * n);
      textt->setColor(0, 0, 0, 255);
      addEntity(textt);
      n++;
    }
  }

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  addEntity(new Button("назад", fontt, 150, 30, X + 100, Y, []()
                       { gui->menu(); }));

  addEntity(new Button("очистить", fontt, 150, 30, X - 100, Y, []()
                       { remove("records.bin"); }));
}

Gui::~Gui() {}
