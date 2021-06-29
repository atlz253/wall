#ifndef UNIT
#define UNIT

#include <string>

#include "entity.hpp"
#include "globals.hpp"

/*
    Базовый класс игрового юнита
*/
class Unit : public RotateEntity
{
 protected:
  Uint32 _id;                 // уникальный номер юнита
  Uint16 _hp;                 // количество жизней юнита
  Uint16 _speed;              // скорость юнита
  Uint16 _damage;             // урон юнита
  Uint16 _backRange;          // радиус действия сзади
  Uint16 _frontRange;         // радиус действия спереди
  static Uint32 _unitsCount;  // количество юнитов за всю игру

 public:
  Unit();

  /*
      Метод вызывается при каждой перерисовке кадра перед отрисовкой на экран.
      Здесь происходит изменение состояния и параметров сущности.
  */
  void process() override;

  virtual void process(Unit *next);

  /*
      Получение точки затылка юнита
  */
  virtual int getBack(void);

  /*
      Получение лицевой точки юнита
  */
  virtual int getFront(void);

  Uint16 getHealth(void);

  Uint32 getId(void);

  virtual Uint16 getReward(void);

  Uint32 getCount(void);

  /*
      Получение урона
  */
  virtual void setDamage(Uint16 damage);

  ~Unit();
};

#endif
