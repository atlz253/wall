#include "graphic.hpp"

int main(void)
{
    Logger *logger = new Logger("trace");
    SdlWindow *window = new SdlWindow(logger);

    window->init();
    while (window->checkEvent())
    {
        window->updateRenderer();
    }

    return 0;
}