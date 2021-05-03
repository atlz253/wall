#include "main.hpp"

void Main::_gameLoop(void)
{
    while (_window->checkEvent())
    {
        _window->updateRenderer();
    }
}

Main::Main()
{
    _logger = new Logger("trace");
    _window = new SdlWindow(_logger);
}

int Main::run(void)
{
    _gameLoop();

    return 0;
}

Main::~Main()
{
    _logger->trace("Main: удаление окна");
    delete _window;

    _logger->trace("Main: удаление логгера");
    delete _logger;
}