#ifndef GLOBAL
#define GLOBAL

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

namespace global
{
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
}

const int SCREEN_WIDTH = 1280; // TODO: remove
const int SCREEN_HEIGHT = 720; // TODO: remove

#endif // GLOBAL