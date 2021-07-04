#include "gui.hpp"

#include <fstream>

#include "button.hpp"
#include "globals.hpp"
#include "input.hpp"
#include "text.hpp"

static const int X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
static const int Y = (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2;

Gui::Gui() : Layer() {}

void Gui::menu(void)
{
  SDL_Event *event;

  clear();

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = P1_INPUT_EVENT;
  addEntity(new Button("играть", X, Y - BUTTON_HEIGHT * 4, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = RECORDS_EVENT;
  addEntity(new Button("рекорды", X, Y - BUTTON_HEIGHT * 3, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = RULE_EVENT;
  addEntity(new Button("правила", X, Y - BUTTON_HEIGHT * 2, event));

  event = new SDL_Event;
  event->type = SDL_QUIT;
  addEntity(new Button("выход", X, Y - BUTTON_HEIGHT, event));
}

void Gui::rules(void)
{
  int w, h;
  SDL_Event *event = new SDL_Event;
  std::string text[3] = {"Бросьте вызов своему противнику и одолейте его в честной схватке!",
                         "Вызывайте своих доблестных бойцов клавишами Q для левого игрока и ",
                         "клавишу } для правого. Победитель получит все!"};

  clear();

  font->getSize(text[0], FONT_SMALL, &w, &h);
  addEntity(new Text(text[0], FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h * 2));
  font->getSize(text[1], FONT_SMALL, &w, &h);
  addEntity(new Text(text[1], FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h * 1));
  font->getSize(text[2], FONT_SMALL, &w, &h);
  addEntity(new Text(text[2], FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2));

  event->type = SDL_USEREVENT;
  event->user.code = MENU_EVENT;
  addEntity(new Button("назад", X, (SCREEN_HEIGHT - h) / 2 + BUTTON_HEIGHT, event));
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
      font->getSize(text, FONT_SMALL, &w, &h);
      addEntity(new Text(text, FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2, h * n));
      n++;
    }
  }

  event->type = SDL_USEREVENT;
  event->user.code = MENU_EVENT;
  addEntity(new Button("назад", X + 100, Y, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = CLEAR_RECORDS_EVENT;
  addEntity(new Button("очистить", X - 100, Y, event));
}

void Gui::p1_input(void)
{
  int w, h;
  SDL_Event *event;

  clear();

  font->getSize("введите имя 1 игрока", FONT_SMALL, &w, &h);
  addEntity(new Text("введите имя 1 игрока", FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2,
                     (SCREEN_HEIGHT - h) / 2 - h * 3));
  addEntity(new Input(p1, FONT_SMALL, {0, 0, 0, 255}, SCREEN_WIDTH / 2, Y - BUTTON_HEIGHT));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = MENU_EVENT;
  addEntity(new Button("назад", X - 100, Y, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = P2_INPUT_EVENT;
  addEntity(new Button("далее", X + 100, Y, event));
}

void Gui::p2_input(void)
{
  int w, h;
  SDL_Event *event;

  clear();

  font->getSize("введите имя 2 игрока", FONT_SMALL, &w, &h);
  addEntity(new Text("введите имя 2 игрока", FONT_SMALL, {0, 0, 0, 255}, (SCREEN_WIDTH - w) / 2,
                     (SCREEN_HEIGHT - h) / 2 - h * 3));
  addEntity(new Input(p2, FONT_SMALL, {0, 0, 0, 255}, SCREEN_WIDTH / 2, Y - BUTTON_HEIGHT));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = P1_INPUT_EVENT;
  addEntity(new Button("назад", X - 100, Y, event));

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = START_EVENT;
  addEntity(new Button("старт", X + 100, Y, event));
}

Gui::~Gui() {}
