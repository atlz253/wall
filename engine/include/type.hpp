#ifndef TYPE
#define TYPE

typedef struct Rect
{
    int16_t x, y;
    uint16_t w, h;
} Rect;

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct SDL_Texture Texture;

typedef struct SDL_Color Color;

typedef enum
{
    FLIP_NONE = 0,
    FLIP_HORIZONTAL = 1,
    FLIP_VERTICAL = 2
} Flip;

typedef struct _TTF_Font Font;

#endif // TYPE