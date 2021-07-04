#include "unit.hpp"

#include <string>

#define BASE_HP 2000

/*
    База игроков, которые они должны охранять как зеницу ока
*/
class Base final : public Unit
{
private:
    Uint16 _money;
    Uint8 _earnSpeed;
    std::string name;

    void _defeat(void);

public:
    Base(int x = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    Unit *keyCheck(void);

    /*
      Получение точки затылка юнита
  */
    int getBack(void) override;

    /*
      Получение лицевой точки юнита
  */
    int getFront(void) override;

    Uint16 getMoney(void);

    void addMoney(Uint16 money);

    void setDamage(Uint16 damage) override;

    void process(void) override;
};
