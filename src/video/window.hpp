#ifndef SDLWINDOW
#define SDLWINDOW

typedef struct SDL_Renderer SDL_Renderer;

class Entity;

extern SDL_Renderer *renderer;

class Window final
{
public:
    Window();

    void freeze(void);

    void clear(void);

    void draw(void);

    ~Window();
};

#endif
