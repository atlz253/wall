#include "wrapper.hpp"

#include "event.hpp"

extern "C"
{
    EXPORT bool EventCheck()
    {
        return events::check();
    }
}