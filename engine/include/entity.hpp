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

  Flip _flip;   // Значение переворота текстуры
  double _angle;        // угол вращения
  Point *_center; // Центр вращения сущности

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
