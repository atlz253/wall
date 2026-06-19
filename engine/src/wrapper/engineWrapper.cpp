#include "wrapper.hpp"

#include "engine.hpp"

extern "C"
{
    EXPORT bool EngineInit(INT32 w, INT32 h)
    {
        return engine::init(w, h);
    }

    EXPORT bool EngineQuit()
    {
        return engine::quit();
    }

    EXPORT bool RenderClear()
    {
        return render::clear();
    }

    EXPORT void RenderPresent()
    {
        render::present();
    }
}