#include "main.hpp"
#include "print.hpp"
#include "entity.hpp"

void Main::_gameLoop(void)
{
    while (_window->checkEvent())
    {
        _window->updateRenderer();
    }
}

Main::Main()
{
    _window = new SdlWindow();
}

int Main::run(void)
{
    _gameLoop();

    return 0;
}

Main::~Main()
{
    printTrace("Main: удаление окна");
    delete _window;
}