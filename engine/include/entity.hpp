#ifndef ENTITY
#define ENTITY

#include <string>

#include "type.hpp"

/*
    Базовая игровая сущность
*/
class Entity
{
protected:
    Rect *_tile;     // Область текстуры
    Rect *_geometry; // Геометрия сущности

    Texture *_texture; // Текстура сущности

    Flip _flip;     // Значение переворота текстуры
    double _angle;  // угол вращения
    Point *_center; // Центр вращения сущности

    Texture *getTexture(std::string path);

public:
    Entity();
    Entity(UINT16 w, UINT16 h, INT16 x = 0, INT16 y = 0); // TODO: use struct Rect
    Entity(std::string path, UINT16 w, UINT16 h, INT16 x = 0, INT16 y = 0);
    Entity(std::string path, UINT16 entityW, UINT16 entityH, INT16 entityX, INT16 entityY, UINT16 tileW, UINT16 tileH, INT16 tileX, INT16 tileY);

    /*
      Конструктор копирования
      Копия будет указывать на ту же текстуру
    */
    Entity(Entity *&entity, int x = 0, int y = 0);

    /* Size functions */

    UINT16 GetWidth(void);
    UINT16 GetHeight(void);

    void SetWidth(UINT16 w);
    void SetHeight(UINT16 h);
    void SetSize(UINT16 w, UINT16 h);

    /* Position functions */

    INT16 GetX(void);
    INT16 GetY(void);

    void SetX(INT16 x);
    void SetY(INT16 y);
    void SetPosition(INT16 x, INT16 y);

    /* Tile functions */

    UINT16 GetTileW(void);
    UINT16 GetTileH(void);

    void SetTileW(UINT16 w);
    void SetTileH(UINT16 h);
    void SetTileSize(UINT16 w, UINT16 h);

    INT16 GetTileX(void);
    INT16 GetTileY(void);

    void SetTileX(INT16 x);
    void SetTileY(INT16 y);
    void SetTilePosition(INT16 x, INT16 y);

    void SetTile(Rect tile);

    /* Texture functions */
    
    void SetTexture(const char* path);

    /*
      Изменение угла наклона
      Без параметров угол установится в 0
    */
    void setAngle(const double angle = 0);

    /*
      Установка центра сущности
      Координаты выставляются относительно геометрии сущности
      Без параметров центр будет установлен в верхнем левом углу сущности
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
    void setFlip(const Flip flip = FLIP_NONE);

    /*
      Получение направления сущности
    */
    Flip getFlip(void);

    /*
      Метод вызывается при каждой перерисовке кадра перед отрисовкой на экран.
      Здесь происходит изменение состояния и параметров сущности.
    */
    virtual void process(void);

    /*
      Отрисовка сущности на экран
    */
    virtual void render(void);

    ~Entity();
};

#endif
