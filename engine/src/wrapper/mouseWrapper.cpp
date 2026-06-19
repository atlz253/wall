#include "wrapper.hpp"

#include "mouse.hpp"

extern "C"
{
    Point MousePosition(void)
    {
        return mouse::Position();
    }

    bool MouseLeftClick(void)
    {
        return mouse::LeftClick();
    }
}