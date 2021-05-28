#ifndef UNIT
#define UNIT

#include <string>

#include "entity.hpp"

/*
    Базовый класс игрового юнита
*/
class Unit : public RotateEntity
{
 protected:
  unsigned short int _hp;          // количество жизней юнита
  unsigned short int _speed;       // скорость юнита
  unsigned short int _backRange;   // радиус действия сзади
  unsigned short int _frontRange;  // радиус действия спереди

 public:
  Unit();

  /*
      Метод вызывается при каждой перерисовке кадра перед отрисовкой на экран.
      Здесь происходит изменение состояния и параметров сущности.
  */
  virtual void process(Unit *next);

  /*
      Получение точки затылка юнита
  */
  virtual int getBack(void);

  /*
      Получение лицевой точки юнита
  */
  virtual int getFront(void);

  /*
      Получение урона
  */
  void getDamage(unsigned short int damage);

  ~Unit();
};

#endif
