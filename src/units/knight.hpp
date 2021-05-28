#include "unit.hpp"

class Knight final : public Unit
{
 private:
  int _frame;           // Текущий кадр
  int _frameCount;      // Счетчик обновления текстуры
  int _animationSpeed;  // Скорость анимации
  bool _isRuning;       // Перемещается ли персонаж?
 public:
  Knight(int x = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void process(Unit *next);

  /*
      Получение точки затылка юнита
  */
  int getBack(void) override;

  /*
      Получение лицевой точки юнита
  */
  int getFront(void) override;

  ~Knight();
};