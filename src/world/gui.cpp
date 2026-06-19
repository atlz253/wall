#include "gui.hpp"

#include <fstream>
#include <iostream>

#include "SDL.h"

#include "base.hpp"
#include "event.hpp"
#include "globals.hpp"
#include "interface.hpp"
#include "keyboard.hpp"
#include "storage.hpp"

static const int X = (SCREEN_WIDTH - 150) / 2;
static const int Y = (SCREEN_HEIGHT - 30) / 2;

namespace
{
SDL_GameController *controller = nullptr;
bool prevUp = false;
bool prevDown = false;
bool prevAccept = false;
bool prevBack = false;

SDL_GameController *getController()
{
  if (controller)
    return controller;

  for (int i = 0; i < SDL_NumJoysticks(); ++i)
  {
    if (SDL_IsGameController(i))
    {
      controller = SDL_GameControllerOpen(i);
      if (controller)
        std::cout << "Controller opened: " << SDL_GameControllerName(controller) << std::endl;
      break;
    }
  }

  return controller;
}

bool pressed(bool value, bool &previous)
{
  bool result = value && !previous;
  previous = value;
  return result;
}

void exitGame()
{
#ifdef __EMSCRIPTEN__
  gui->menu();
#else
  events::quit();
#endif
}
}

Gui::Gui() : Layer()
{
  _buttonsCount = 0;
  _selectedButton = 0;
  for (int i = 0; i < 4; ++i)
    _buttons[i] = nullptr;
}

void Gui::addButton(Button *button)
{
  if (_buttonsCount < 4)
  {
    button->setSelected(_buttonsCount == 0);
    _buttons[_buttonsCount++] = button;
  }
  addEntity(button);
}

void Gui::processInput(void)
{
  if (!_buttonsCount)
    return;

  keys state = keyboard::state(nullptr);
  SDL_GameController *pad = getController();
  bool up = state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
  bool down = state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
  bool accept = state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE];
  bool back = state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_BACKSPACE];

  if (pad)
  {
    up = up || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_UP);
    down = down || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    accept = accept || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_START);
    back = back || SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B);
  }

  if (pressed(up, prevUp))
    _selectedButton = (_selectedButton + _buttonsCount - 1) % _buttonsCount;
  if (pressed(down, prevDown))
    _selectedButton = (_selectedButton + 1) % _buttonsCount;

  for (int i = 0; i < _buttonsCount; ++i)
    _buttons[i]->setSelected(i == _selectedButton);

  if (pressed(accept, prevAccept))
    _buttons[_selectedButton]->click();
  if (pressed(back, prevBack))
    menu();
}

void Gui::renderer(void)
{
  processInput();
  Layer::renderer();
  button::runPendingEvents();
}

void Gui::menu(void)
{
  clear();
  _buttonsCount = 0;
  _selectedButton = 0;

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  addButton(new Button("play", fontt, 150, 30, X, Y - 30 * 4, []()
                       {
                         gui->clear();
                         action->start();
                       }));

  addButton(new Button("records", fontt, 150, 30, X, Y - 30 * 3, []()
                       { gui->records(); }));

  addButton(new Button("rules", fontt, 150, 30, X, Y - 30 * 2, []()
                       { gui->rules(); }));

  addButton(new Button("exit", fontt, 150, 30, X, Y - 30, []()
                       { exitGame(); }));
}

void Gui::rules(void)
{
  int w, h;
  std::string text[3] = {"Challenge your opponent and defeat their base.",
                         "Create units with L1 for the left player",
                         "and R1 for the right player."};

  clear();
  _buttonsCount = 0;
  _selectedButton = 0;

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  Text *textt = new Text(text[0], fontt);
  textt->getSize(&w, &h);
  textt->SetPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h * 2);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  textt = new Text(text[1], fontt);
  textt->getSize(&w, &h);
  textt->SetPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 - h);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  textt = new Text(text[2], fontt);
  textt->getSize(&w, &h);
  textt->SetPosition((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
  textt->setColor(0, 0, 0, 255);
  addEntity(textt);

  addButton(new Button("back", fontt, 150, 30, X, (SCREEN_HEIGHT - h) / 2 + 30, []()
                       { gui->menu(); }));
}

void Gui::records(void)
{
  record *rec = new record;
  std::string text;
  std::ifstream file(storage::recordsPath(), std::ios::binary);

  clear();
  _buttonsCount = 0;
  _selectedButton = 0;

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
      textt->SetPosition((SCREEN_WIDTH - w) / 2, h * n);
      textt->setColor(0, 0, 0, 255);
      addEntity(textt);
      n++;
    }
  }

  Font *fontt = font::open("res/joystix_monospace.ttf", 20);

  addButton(new Button("back", fontt, 150, 30, X + 100, Y, []()
                       { gui->menu(); }));

  addButton(new Button("clear", fontt, 150, 30, X - 100, Y, []()
                       {
                         remove(storage::recordsPath());
                         storage::sync();
                       }));

  delete rec;
}

Gui::~Gui() {}
