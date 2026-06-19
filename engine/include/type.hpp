#ifndef TYPE
#define TYPE

#include <cstdint>

#define INT16 std::int16_t
#define INT32 std::int32_t

#define UINT8 std::uint8_t
#define UINT16 std::uint16_t

typedef struct Rect
{
    INT16 x = 0;
    INT16 y = 0;
    UINT16 w = 0;
    UINT16 h = 0;
} Rect;

typedef struct Point
{
    INT32 x = 0;
    INT32 y = 0;
} Point;

typedef struct SDL_Texture Texture;

typedef struct Color
{
    UINT8 r = 255;
    UINT8 g = 255;
    UINT8 b = 255;
    UINT8 a = 255;
} Color;

#define COLOR_WHITE {(UINT8)255, (UINT8) 255, (UINT8) 255, (UINT8) 255}
#define COLOR_BLACK {(UINT8)0, (UINT8)0, (UINT8)0, (UINT8)0}

typedef enum
{
    FLIP_NONE = 0,
    FLIP_HORIZONTAL = 1,
    FLIP_VERTICAL = 2
} Flip;

typedef struct _TTF_Font Font;

#endif // TYPE