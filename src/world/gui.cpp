#include "gui.hpp"

#include "button.hpp"
#include "text.hpp"

static const int X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
static const int Y = (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2;

Gui::Gui() : Layer() {}

void Gui::menu(void)
{
  SDL_Event* event;

  clear();

  event = new SDL_Event;
  event->type = SDL_USEREVENT;
  event->user.code = START_EVENT;
  addEntity(new Button("играть", X, Y - BUTTON_HEIGHT * 4, event));

  addEntity(new Button("рекорды", X, Y - BUTTON_HEIGHT * 3, nullptr));

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
  SDL_Event* event = new SDL_Event;
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

Gui::~Gui() {}
