#include "gui.hpp"

#include <fstream>

#include "button.hpp"
#include "globals.hpp"
#include "text.hpp"
#include "event.hpp"

static const int X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
static const int Y = (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2;

Gui::Gui() : Layer() {}

void Gui::menu(void)
{
  SDL_Event *event;

  clear();

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  addEntity(new Button("играть", fontt, X, Y - BUTTON_HEIGHT * 4, []() {
    gui->clear();
    action->start();
  }));

  addEntity(new Button("рекорды", fontt, X, Y - BUTTON_HEIGHT * 3, []() {gui->records();}));

  addEntity(new Button("правила", fontt, X, Y - BUTTON_HEIGHT * 2, []() {gui->rules();}));

  addEntity(new Button("выход", fontt, X, Y - BUTTON_HEIGHT, []() {events::quit();}));
}

void Gui::rules(void)
{
  int w, h;
  SDL_Event *event = new SDL_Event;
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

  addEntity(new Button("назад", fontt, X, (SCREEN_HEIGHT - h) / 2 + BUTTON_HEIGHT, []() {gui->menu();}));
}

void Gui::records(void)
{
  record *rec = new record;
  std::string text;
  SDL_Event *event = new SDL_Event;
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

  addEntity(new Button("назад", fontt, X + 100, Y, []() {gui->menu();}));

  addEntity(new Button("очистить", fontt, X - 100, Y, []() {remove("records.bin");}));
}

Gui::~Gui() {}
