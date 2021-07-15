#include "unit.hpp"

#define KNIGHT_COST 100

class Knight final : public Unit
{
private:
  uint8_t _frame;          // Текущий кадр
  uint8_t _frameCount;     // Счетчик обновления текстуры
  uint8_t _animationSpeed; // Скорость анимации
  bool _isRuning;          // Перемещается ли персонаж?
public:
  Knight(int x = 0, Flip flip = FLIP_NONE);

  void process(Unit *next);

  /*
      Получение точки затылка юнита
  */
  int getBack(void) override;

  /*
      Получение лицевой точки юнита
  */
  int getFront(void) override;

  uint16_t getReward(void) override;

  ~Knight();
};
