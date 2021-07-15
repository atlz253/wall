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
    Texture *_texture; // Текстура сущности
    Rect *_geometry;   // Геометрия сущности
    Rect *_tile;       // Область текстуры

    Texture *getTexture(std::string path);

public:
    Entity();

    Entity(int w, int h, int x = 0, int y = 0);

    Entity(std::string path, int w, int h, int x = 0, int y = 0);

    Entity(std::string path, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX, int tileY);

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
    virtual void render(void);

    ~Entity();
};

/*
    Игровая сущность с возможностью вращения текстуры
*/
class RotateEntity : public Entity
{
protected:
    double _angle = 0;        // угол вращения
    Point *_center = nullptr; // Центр вращения сущности
    Flip _flip = FLIP_NONE;   // Значение переворота текстуры
public:
    RotateEntity();

    RotateEntity(std::string path, int w, int h, int x = 0, int y = 0, Flip flip = FLIP_NONE);

    RotateEntity(std::string path, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX, int tileY, Flip flip = FLIP_NONE);

    /*
      Конструктор копирования
      Копия будет указывать на ту же текстуру
  */
    RotateEntity(RotateEntity *&entity, Flip flip, int x = 0, int y = 0);

    /*
      Конструктор копирования
      Копия будет указывать на ту же текстуру
      int entityW, entityH - ширина и высота сущности
      int entityX, entityY - расположение сущности
      int tileW, tileH - ширина и высота области текстуры
      int tileX, tileY - располажение области текстуры
      SDL_RendererFlip flip - параметр поворота текстуры
  */
    RotateEntity(Entity *&entity, int entityW, int entityH, int entityX, int entityY, int tileW, int tileH, int tileX,
                 int tileY, Flip flip = FLIP_NONE);

    /*
      Отрисовка сущности на экран
  */
    void render(void) override;

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

    ~RotateEntity();
};

#endif
