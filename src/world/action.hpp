#include <list>
#include "unit.hpp"

class Action final // TODO: сделать Layer - шаблоном?
{
private:
    std::list<Unit *> _list;               // Список сущностей
    std::list<Unit *>::iterator _iterator; // Итератор для работы со списком
public:
    Action(Renderer *renderer);

    void renderer(void);
};