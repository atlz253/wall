#include <queue>

#include "unit.hpp"

class Action final  // TODO: сделать Layer - шаблоном?
{
 private:
  std::queue<Unit*> *_leftTeam;
  std::queue<Unit*> *_rightTeam;

 public:
  Action(Renderer *renderer);

  void renderer(void);

  ~Action();
};
