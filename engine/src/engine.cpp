#include "engine.hpp"

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "event.hpp"
#include "global.hpp"
#include "textureManager.hpp"
namespace engine
{
    static void logRenderDrivers()
    {
        SDL_RendererInfo info;
        int count = SDL_GetNumRenderDrivers();

        std::cout << "SDL render drivers:";
        for (int i = 0; i < count; ++i)
        {
            if (SDL_GetRenderDriverInfo(i, &info) == 0)
                std::cout << " " << info.name;
        }
        std::cout << std::endl;
    }

    bool init(INT32 w, INT32 h)
    {
        std::cout << "SdlSubSystem: SDL2 initialization" << std::endl;
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK))
        {
            std::cout << "SDL2 initialization error:" << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        /*
            Не отключать композитор рабочих столов на linux дистрибутивах
        */
       #ifdef __unix__
        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
       #endif

        std::cout << "SdlSubSystem: SDL2_Image initialization" << std::endl;
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            std::cout << "SDL2_Image initialization error:" << IMG_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "SdlSubSystem: SDL2_ttf initialization" << std::endl;
        if (TTF_Init())
        {
            std::cout << "SDL2_Image initialization error:" << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "SDL video driver: " << SDL_GetCurrentVideoDriver() << std::endl;
        logRenderDrivers();

        SDL_DisplayMode displayMode;
        int windowW = w;
        int windowH = h;
        if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0 && displayMode.w > 0 && displayMode.h > 0)
        {
            windowW = displayMode.w;
            windowH = displayMode.h;
            std::cout << "SDL display mode: " << windowW << "x" << windowH << std::endl;
        }

        std::cout << "Creating window" << std::endl;
        global::window = SDL_CreateWindow("engine", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, windowW,
                                          windowH, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        if (!global::window)
        {
            std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Window created" << std::endl;
        std::cout << "Creating accelerated renderer" << std::endl;
        global::renderer = SDL_CreateRenderer(global::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!global::renderer)
        {
            std::cout << "Failed to create accelerated renderer:" << SDL_GetError() << std::endl;
            std::cout << "Creating software renderer" << std::endl;
            global::renderer = SDL_CreateRenderer(global::window, -1, SDL_RENDERER_SOFTWARE);
        }
        if (!global::renderer)
        {
            std::cout << "Failed to create software renderer:" << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        SDL_RendererInfo rendererInfo;
        if (SDL_GetRendererInfo(global::renderer, &rendererInfo) == 0)
            std::cout << "Renderer created: " << rendererInfo.name << std::endl;
        else
            std::cout << "Renderer created" << std::endl;
        SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "letterbox");
        if (SDL_RenderSetLogicalSize(global::renderer, w, h))
            std::cout << "Failed to set logical size:" << SDL_GetError() << std::endl;
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRenderDrawBlendMode(global::renderer, SDL_BLENDMODE_BLEND); // TODO: read docs about this

        events::init();
        textures::init();

        return false;
    }

    bool quit()
    {
        SDL_DestroyWindow(global::window);
        SDL_DestroyRenderer(global::renderer);

        std::cout << "SdlSubSystem: завершение работы SDL2" << std::endl;
        SDL_Quit();

        std::cout << "SdlSubSystem: завершение работы SDL2_Image" << std::endl;
        IMG_Quit();

        std::cout << "SdlSubSystem: завершение работы SDL2_ttf" << std::endl;
        TTF_Quit();

        return false;
    }
}

namespace render
{
    bool clear()
    {
        if (!SDL_RenderClear(global::renderer))
            return false;

        return true;
    }

    void present()
    {
        SDL_RenderPresent(global::renderer);
    }
}
