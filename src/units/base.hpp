#include "unit.hpp"

#include <string>

#define BASE_HP 2000

/*
    База игроков, которые они должны охранять как зеницу ока
*/
class Base final : public Unit
{
private:
  uint16_t _money;
  uint8_t _earnSpeed;
  std::string name;

  void _defeat(void);

public:
  Base(int x = 0, Flip flip = FLIP_NONE);

  Unit *keyCheck(void);

  /*
      Получение точки затылка юнита
  */
  int getBack(void) override;

  /*
      Получение лицевой точки юнита
  */
  int getFront(void) override;

  uint16_t getMoney(void);

  void addMoney(uint16_t money);

  void setDamage(uint16_t damage) override;

  void process(void) override;
};
