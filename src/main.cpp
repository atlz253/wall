#include "graphic.hpp"
#include "logger/logger.hpp"

int main(void)
{
    Logger *logger = new Logger("trace");
    SdlWindow *window = new SdlWindow(logger);
    window->createWindow();

    return 0;
}