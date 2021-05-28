#include "background.hpp"

#include "entity.hpp"
#include "print.hpp"
#include "renderer.hpp"

class Clouds : public Entity
{
 private:
  int _startPosition = 0;  // Начальная позиция облака
  int _frame = 0;          // Индикатор для отрисовки

 public:
  Clouds(Renderer *renderer, std::string path, int w, int h, int x = 0, int y = 0) : Entity(renderer, path, w, h, x, y)
  {
    _startPosition = x;
  }

  Clouds(Entity *entity, int x = 0, int y = 0) : Entity(entity, x, y) { _startPosition = x; }

  void process(void) override
  {
    if (++_frame == 3)
    {
      _geometry->x += 1;
      _frame = 0;
    }
  }

  void render(void) override
  {
    if (_geometry->x <= 1280) Entity::render();

    if (_geometry->x - _startPosition == 1088) _geometry->x = _startPosition;
  }
};

Background::Background(Renderer *renderer)
{
  Entity *p;

  printTrace("Terrain: инициализация заднего плана");
  printTrace("Background: создаем небесную твердь");
  p = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/sky.png", 124, 608);
  _list.push_back(p);
  for (int i = 1; i < 11; i++) _list.push_back(new Entity(p, i * 124));

  printTrace("Background: разливаем воду");
  p = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/sea.png", 124, 192, 0, 608);
  _list.push_back(p);
  for (int i = 1; i < 11; i++) _list.push_back(new Entity(p, i * 124, 608));

  printTrace("Background: сгущаем облака");
  p = new Clouds(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png", 1088, 472, 0, 136);
  _list.push_back(p);
  _list.push_back(new Clouds(p, -1088, 136));
  _list.push_back(new Clouds(p, 1088, 136));

  printTrace("Background: создаем далекие земели");
  _list.push_back(new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/far-grounds.png", 1232, 220, 24, 388));

  printTrace("Terrain: распыляем темноту");
  p = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/tileset.png", 16 * 22, 16 * 6, 480, 560);
  p->setTile(112, 272, 16, 16);
  _list.push_back(p);
  p = new Entity(p, 1120, 592);
  p->setSize(16 * 10, 16 * 8);
  _list.push_back(p);
}
