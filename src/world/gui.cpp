#include "gui.hpp"

#include <fstream>

#include "button.hpp"
#include "globals.hpp"
#include "text.hpp"
#include "engine.hpp" // TODO: remove

static const int X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
static const int Y = (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2;

Gui::Gui() : Layer() {}

void Gui::menu(void)
{
  SDL_Event *event;

  clear();

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = START_EVENT;
  addEntity(new Button("играть", fontt, X, Y - BUTTON_HEIGHT * 4, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = RECORDS_EVENT;
  addEntity(new Button("рекорды", fontt, X, Y - BUTTON_HEIGHT * 3, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = RULE_EVENT;
  addEntity(new Button("правила", fontt, X, Y - BUTTON_HEIGHT * 2, event));

  event = new SDL_Event;
  event->type = SDL_QUIT;
  addEntity(new Button("выход", fontt, X, Y - BUTTON_HEIGHT, event));
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

  event->type = SDL_USEREVENT;
  event->user.code = MENU_EVENT;
  addEntity(new Button("назад", fontt, X, (SCREEN_HEIGHT - h) / 2 + BUTTON_HEIGHT, event));
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

  event->type = SDL_USEREVENT;
  event->user.code = MENU_EVENT;
  addEntity(new Button("назад", fontt, X + 100, Y, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = CLEAR_RECORDS_EVENT;
  addEntity(new Button("очистить", fontt, X - 100, Y, event));
}

void Gui::p1_input(void)
{
}

void Gui::p2_input(void)
{  
}

Gui::~Gui() {}
