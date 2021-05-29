#include <queue>

#include "unit.hpp"

class Base;

class Action final  // TODO: сделать Layer - шаблоном?
{
 private:
  std::queue<Unit*> *_leftTeam;
  std::queue<Unit*> *_rightTeam;

  Base *_leftBase;
  Base *_rightBase;

 public:
  Action(Renderer *renderer);

  void renderer(void);

  ~Action();
};
