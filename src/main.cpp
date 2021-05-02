#include "graphic.hpp"
#include "logger.hpp"

int main(void)
{
    Logger *logger = new Logger("trace");
    SdlWindow *window = new SdlWindow(logger);

    window->init();
    while (window->checkEvent())
        ;

    return 0;
}