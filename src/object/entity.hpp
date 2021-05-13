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
        Конструктор копирования
        Копия будет указывать на ту же текстуру
        int entityW, entityH - ширина и высота сущности
        int entityX, entityY - расположение сущности
        int tileW, tileH - ширина и высота области текстуры
        int tileX, tileY - располажение области текстуры
    */
    Entity(Entity *&entity, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX, int tileY);

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

/*
    Игровая сущность с возможностью вращения текстуры
*/
class RotateEntity : public Entity
{
protected:
    double _angle = 0;                      // угол вращения
    SDL_Point *_center = nullptr;           // Центр вращения сущности
    SDL_RendererFlip _flip = SDL_FLIP_NONE; // Значение переворота текстуры
public:
    /*
        Инициализация сущности:
        Texture texture - текстура сущности
        int w, h - ширина и высота сущности
        int x, y - расположение сущности (по-умолчанию верхний левый угол)
    */
    RotateEntity(Renderer *renderer, std::string path, int w, int h, int x = 0, int y = 0) : Entity(renderer, path, w, h, x, y) {}

    /*
        Конструктор копирования
        Копия будет указывать на ту же текстуру
    */
    RotateEntity(Entity *&entity, int x = 0, int y = 0) : Entity(entity, x, y) {}

    /*
        Конструктор копирования
        Копия будет указывать на ту же текстуру
        int entityW, entityH - ширина и высота сущности
        int entityX, entityY - расположение сущности
        int tileW, tileH - ширина и высота области текстуры
        int tileX, tileY - располажение области текстуры
        SDL_RendererFlip flip - параметр поворота текстуры
    */
    RotateEntity(Entity *&entity, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX, int tileY, SDL_RendererFlip flip = SDL_FLIP_NONE);

    /*
        Отрисовка сущности на экран
    */
    void renderer(void) override;

    /*
        Изменение угла наклона
        Без параметров угол установится в 0
    */
    void setAngle(const double angle = 0);

    /*
        Установка центра сущности
        Без параметров центр будет установлен в верхнем левом углу
    */
    void setCenter(const int x = 0, const int y = 0);

    /*
        Установка параметров поворота текстуры
        Без параметров текстура переворачиваться не будет
        
        Возможные параметры:
        SDL_FLIP_NONE                           - текстура переворачиваться не будет
        SDL_FLIP_VERTICAL                       - текстура отразиться по вертикали
        SDL_FLIP_HORIZONTAL                     - текстура отразиться по горизонтали
        SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL - текстура отразиться по диагонали
    */
    void setFlip(const SDL_RendererFlip flip = SDL_FLIP_NONE);

    ~RotateEntity();
};

#endif
