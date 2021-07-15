#ifndef ACTION
#define ACTION

#include <queue>

#include "layer.hpp"

class Unit;
class Base;

class Action final : public Layer
{
private:
  std::queue<Unit *> *_leftTeam;
  std::queue<Unit *> *_rightTeam;
  std::queue<Unit *> *_deathQueue;

  bool action;

  Base *_leftBase;
  Base *_rightBase;

  void _unitsRenderer(void);

  void _baseRenderer(void);

public:
  Action();

  void start(void);

  void stop(void);

  void renderer(void) override;

  void clear(void) override;

  ~Action();
};

#endif // ACTION
