#include "background.hpp"

#include <iostream>

#include "entity.hpp"
#include "globals.hpp"

class Clouds : public Entity
{
private:
  int _startPosition = 0; // Начальная позиция облака
  int _frame = 0;         // Индикатор для отрисовки

public:
  Clouds(int w, int h, int x = 0, int y = 0) : Entity()
  {
    _texture = getTexture("res/Magic-Cliffs-Environment/PNG/clouds.png");

    _geometry->w = w;
    _geometry->h = h;

    _geometry->x = x;
    _geometry->y = y;

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
    if (_geometry->x <= 1280)
      Entity::render();

    if (_geometry->x - _startPosition == 1088)
      _geometry->x = _startPosition;
  }
};

Background::Background()
{
  Entity *p;

  std::cout << "Terrain: инициализация заднего плана" << std::endl;
  std::cout << "Background: создаем небесную твердь" << std::endl;
  p = new Entity("res/Magic-Cliffs-Environment/PNG/sky.png", 124, 608);
  _queue->push(p);
  for (int i = 1; i < 11; i++)
    _queue->push(new Entity(p, i * 124));

  std::cout << "Background: разливаем воду" << std::endl;
  p = new Entity("res/Magic-Cliffs-Environment/PNG/sea.png", 124, 192, 0, 608);
  _queue->push(p);
  for (int i = 1; i < 11; i++)
    _queue->push(new Entity(p, i * 124, 608));

  std::cout << "Background: сгущаем облака" << std::endl;
  p = new Clouds(1088, 472, 0, 136);
  _queue->push(p);
  _queue->push(new Clouds(p, -1088, 136));
  _queue->push(new Clouds(p, 1088, 136));

  std::cout << "Background: создаем далекие земели" << std::endl;
  _queue->push(new Entity("res/Magic-Cliffs-Environment/PNG/far-grounds.png", 1232, 220, 24, 388));

  std::cout << "Terrain: распыляем темноту" << std::endl;
  p = new Entity("res/Magic-Cliffs-Environment/PNG/tileset.png", 16 * 22, 16 * 6, 480, 560);
  p->setTile(112, 272, 16, 16);
  _queue->push(p);
  p = new Entity(p, 1120, 592);
  p->SetSize(16 * 10, 16 * 8);
  _queue->push(p);
}
