#include "background.hpp"

#include "entity.hpp"
#include "globals.hpp"
#include "print.hpp"
#include "renderer.hpp"

class Clouds : public Entity
{
 private:
  int _startPosition = 0;  // Начальная позиция облака
  int _frame = 0;          // Индикатор для отрисовки

 public:
  Clouds(int w, int h, int x = 0, int y = 0) : Entity()
  {
    if (!textures->key("clouds")) textures->loadTexture("clouds", "res/Magic-Cliffs-Environment/PNG/clouds.png");
    _texture = textures->key("clouds");

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
    if (_geometry->x <= 1280) Entity::render();

    if (_geometry->x - _startPosition == 1088) _geometry->x = _startPosition;
  }
};

Background::Background()
{
  Entity *p;

  printTrace("Terrain: инициализация заднего плана");
  printTrace("Background: создаем небесную твердь");
  textures->loadTexture("res/Magic-Cliffs-Environment/PNG/sky.png");
  p = new Entity(textures->key("res/Magic-Cliffs-Environment/PNG/sky.png"), 124, 608);
  _queue->push(p);
  for (int i = 1; i < 11; i++) _queue->push(new Entity(p, i * 124));

  printTrace("Background: разливаем воду");
  textures->loadTexture("res/Magic-Cliffs-Environment/PNG/sea.png");
  p = new Entity(textures->key("res/Magic-Cliffs-Environment/PNG/sea.png"), 124, 192, 0, 608);
  _queue->push(p);
  for (int i = 1; i < 11; i++) _queue->push(new Entity(p, i * 124, 608));

  printTrace("Background: сгущаем облака");
  p = new Clouds(1088, 472, 0, 136);
  _queue->push(p);
  _queue->push(new Clouds(p, -1088, 136));
  _queue->push(new Clouds(p, 1088, 136));

  printTrace("Background: создаем далекие земели");
  textures->loadTexture("res/Magic-Cliffs-Environment/PNG/far-grounds.png");
  _queue->push(new Entity(textures->key("res/Magic-Cliffs-Environment/PNG/far-grounds.png"), 1232, 220, 24, 388));

  printTrace("Terrain: распыляем темноту");
  textures->loadTexture("res/Magic-Cliffs-Environment/PNG/tileset.png");
  p = new Entity(textures->key("res/Magic-Cliffs-Environment/PNG/tileset.png"), 16 * 22, 16 * 6, 480, 560);
  p->setTile(112, 272, 16, 16);
  _queue->push(p);
  p = new Entity(p, 1120, 592);
  p->setSize(16 * 10, 16 * 8);
  _queue->push(p);
}
