#include "unit.hpp"

/*
    База игроков, которые они должны охранять как зеницу ока
*/
class Base final : public Unit
{
 private:
 public:
  Base(int x = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

  /*
      Получение точки затылка юнита
  */
  int getBack(void) override;

  /*
      Получение лицевой точки юнита
  */
  int getFront(void) override;
};
