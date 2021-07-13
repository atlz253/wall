#include "engine.hpp"

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

namespace engine
{
    int init()
    {
        std::cout << "SdlSubSystem: инициализация SDL2" << std::endl;
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            std::cout << "Ошибка инициализации SDL2:" << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        /*
            Не отключать композитор рабочих столов на linux дистрибутивах
        */
        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

        std::cout << "SdlSubSystem: инициализация SDL2_Image" << std::endl;
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            std::cout << "Ошибка инициализации SDL2_Image:" << IMG_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "SdlSubSystem: инициализация SDL2_ttf" << std::endl;
        if (TTF_Init())
        {
            std::cout << "Ошибка инициализации SDL2_Image:" << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    int quit()
    {
        std::cout << "SdlSubSystem: завершение работы SDL2" << std::endl;
        SDL_Quit();

        std::cout << "SdlSubSystem: завершение работы SDL2_Image" << std::endl;
        IMG_Quit();

        std::cout << "SdlSubSystem: завершение работы SDL2_ttf" << std::endl;
        TTF_Quit();
    }
}