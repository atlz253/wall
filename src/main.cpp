#include "graphic.hpp"
#include "logger.hpp"

int main(void)
{
    Logger *logger = new Logger("trace");
    SdlWindow *window = new SdlWindow(logger);

    window->createWindow();
    while (window->checkEvent())
        ;

    return 0;
}