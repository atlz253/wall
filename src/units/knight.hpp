#include "unit.hpp"

#define KNIGHT_COST 100

class Knight final : public Unit
{
private:
  enum Animation
  {
    RUN,
    IDLE,
    ATTACK,
    DEATH
  };

  int _frame;
  int _frameCount;
  int _animationSpeed;
  int _lastLoggedAnimation;
  uint32_t _lastLoggedTargetId;
  Animation _animation;

  void setAnimation(Animation animation);
  bool advanceAnimation(int frameTotal, const int frames[]);
  const char *animationName(Animation animation) const;
  void logState(Animation animation, Unit *target);

public:
  Knight(int x = 0, Flip flip = FLIP_NONE);

  void process(Unit *next);

  int getBack(void) override;

  int getFront(void) override;

  uint16_t getReward(void) override;

  ~Knight();
};
