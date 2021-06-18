#include "globals.hpp"
#include "unit.hpp"

#define BASE_HP 2000

/*
    База игроков, которые они должны охранять как зеницу ока
*/
class Base final : public Unit
{
 private:
  UINT16 _money;

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

  UINT16 getMoney(void);
};
