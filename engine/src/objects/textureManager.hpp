#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include <string>

typedef struct SDL_Texture SDL_Texture;

namespace textures
{
    int init();

    SDL_Texture *&get(std::string path);

    void clear(std::string path);

    int quit();
}

#endif // TEXTURE_MANAGER