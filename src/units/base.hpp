#include "unit.hpp"

#define BASE_HP 2000

/*
    База игроков, которые они должны охранять как зеницу ока
*/
class Base final : public Unit
{
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
};
