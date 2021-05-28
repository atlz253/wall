#include "unit.hpp"

typedef struct node
{
  Unit *unit;
  node *prev;
  node *next;
} node;

class Base;

class Action final  // TODO: сделать Layer - шаблоном?
{
 private:
  node *_listStart;
  node *_listEnd;

  Base *_baseLeft;
  Base *_baseRight;

  void _add(Unit *unit);

 public:
  Action(Renderer *renderer);

  void renderer(void);

  ~Action();
};
