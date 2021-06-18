#ifndef UNIT
#define UNIT

#include <string>

#include "globals.hpp"
#include "entity.hpp"

/*
    Базовый класс игрового юнита
*/
class Unit : public RotateEntity
{
 protected:
  unsigned int _id;  // уникальный номер юнита
  unsigned short int _hp;           // количество жизней юнита //TODO: заменить на UINT макросы
  unsigned short int _speed;        // скорость юнита
  unsigned short int _damage;       // урон юнита
  unsigned short int _backRange;    // радиус действия сзади
  unsigned short int _frontRange;   // радиус действия спереди
  static unsigned int _unitsCount;  // количество юнитов за всю игру

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

  unsigned short int getHealth(void);

  unsigned short int getId(void);

  virtual UINT16 getReward(void);

  /*
      Получение урона
  */
  virtual void setDamage(unsigned short int damage);

  ~Unit();
};

#endif
