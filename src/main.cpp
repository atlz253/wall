#include <iostream>
#include <SDL2/SDL.h>
#include "graphic.cpp"

int main(void)
{
    SdlWindow *window = new SdlWindow();
    window->createWindow();

    return 0;
}