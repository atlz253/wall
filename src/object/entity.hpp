#ifndef ENTITY
#define ENTITY

#include "SDL.h"
#include <string>

/*
    ====================================================================
    enum SDL_ScaleMode и struct SDL_Texture взяты из исходников SDL2
    src/render/SDL_sysrender.h
*/

typedef struct SDL_SW_YUVTexture SDL_SW_YUVTexture;

typedef enum
{
    SDL_ScaleModeNearest,
    SDL_ScaleModeLinear,
    SDL_ScaleModeBest
} SDL_ScaleMode;

/* Define the SDL texture structure */
struct SDL_Texture
{
    const void *magic;
    Uint32 format;           /**< The pixel format of the texture */
    int access;              /**< SDL_TextureAccess */
    int w;                   /**< The width of the texture */
    int h;                   /**< The height of the texture */
    int modMode;             /**< The texture modulation mode */
    SDL_BlendMode blendMode; /**< The texture blend mode */
    SDL_ScaleMode scaleMode; /**< The texture scale mode */
    Uint8 r, g, b, a;        /**< Texture modulation values */

    SDL_Renderer *renderer;

    /* Support for formats not supported directly by the renderer */
    SDL_Texture *native;
    SDL_SW_YUVTexture *yuv;
    void *pixels;
    int pitch;
    SDL_Rect locked_rect;

    Uint32 last_command_generation; /* last command queue generation this texture was in. */

    void *driverdata; /**< Driver specific texture representation */

    SDL_Texture *prev;
    SDL_Texture *next;
};

/*
    ====================================================================
*/

class Renderer;

/*
    Базовая игровая сущность
*/
class Entity
{
protected:
    SDL_Texture *_texture = nullptr; // Текстура сущности
    SDL_Rect *_geometry = nullptr;   // Геометрия сущности
    SDL_Rect *_tile = nullptr;       // Область текстуры

    /*
        Загрузка текстуры
    */
    void _loadTexture(Renderer *renderer, std::string path);

public:
    Entity();

    /*
        Инициализация сущности:
        Texture texture - текстура сущности
        int w, h - ширина и высота сущности
        int x, y - расположение сущности (по-умолчанию верхний левый угол)
    */
    Entity(Renderer *renderer, std::string path, int w, int h, int x = 0, int y = 0);

    /*
        Конструктор копирования
        Копия будет указывать на ту же текстуру
    */
    Entity(Entity *&entity, int x = 0, int y = 0);

    /*
        Изменение размера сущности
        int w, h - ширина и высота сущности
    */
    void setSize(int w, int h);

    /*
        Изменение положения сущности
        int x, y - расположение сущности
    */
    void setPosition(int x, int y);

    /*
        Изменение используемой области текстуры
        int x, y - координаты области
        int w, h - размер области
    */
    void setTile(int x, int y, int w, int h);

    /*
        Метод вызывается при каждой перерисовке кадра перед отрисовкой на экран.
        Здесь происходит изменение состояния и параметров сущности.
    */
    virtual void process(void);

    /*
        Отрисовка сущности на экран
    */
    virtual void renderer(void);

    ~Entity();
};

#endif
