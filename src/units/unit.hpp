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
  uint32_t _id;                // уникальный номер юнита
  uint16_t _hp;                // количество жизней юнита
  uint16_t _speed;             // скорость юнита
  uint16_t _damage;            // урон юнита
  uint16_t _backRange;         // радиус действия сзади
  uint16_t _frontRange;        // радиус действия спереди
  static uint32_t _unitsCount; // количество юнитов за всю игру

public:
  Unit();

  /*
      Метод вызывается при каждой перерисовке кадра перед отрисовкой на экран.
      Здесь происходит изменение состояния и параметров сущности.
  */
  void process(void) override;

  virtual void process(Unit *next);

  /*
      Получение точки затылка юнита
  */
  virtual int getBack(void);

  /*
      Получение лицевой точки юнита
  */
  virtual int getFront(void);

  uint16_t getHealth(void);

  uint32_t getId(void);

  virtual uint16_t getReward(void);

  uint32_t getCount(void);

  void clearCount(void);

  /*
      Получение урона
  */
  virtual void setDamage(uint16_t damage);

  ~Unit();
};

#endif
