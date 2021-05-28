#include "terrain.hpp"

#include "entity.hpp"
#include "print.hpp"

Terrain::Terrain(Renderer *renderer)
{
  printTrace("Terrain: загрузка тайлсета");
  Entity *tile = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/tileset.png", 16, 16), *tmp = nullptr;

  printTrace("Terrain: инициализация переднего плана");

  printTrace("Terrain: создание левого острова");
  _list.push_back(new RotateEntity(tile, 96 * 2, 112 * 2, 0, 496, 96, 112, 32, 176, SDL_FLIP_HORIZONTAL));

  printTrace("Terrain: создание правого острова");
  _list.push_back(new RotateEntity(tile, 48 * 2, 48 * 2, 1024, 624, 48, 48, 656, 240, SDL_FLIP_HORIZONTAL));
  _list.push_back(new Entity(tile, 48 * 2, 48 * 2, 1184, 496, 48, 48, 192, 176));
  _list.push_back(new RotateEntity(tile, 48 * 2, 64 * 2, 1088, 496, 48, 64, 512, 176, SDL_FLIP_HORIZONTAL));

  printTrace("Terrain: строительство мостов");
  /* левые части мостов */
  tmp = new Entity(tile, 48 * 2, 48 * 2, 128, 504, 48, 48, 576, 176);
  _list.push_back(tmp);
  _list.push_back(new Entity(tmp, 896, 505));

  /* центральные части мостов */
  tmp = new Entity(tmp, 224, 504);
  tmp->setTile(640, 176, 48, 48);
  _list.push_back(tmp);
  _list.push_back(new Entity(tmp, 992, 505));

  /* правые части мостов */
  tmp = new Entity(tmp, 288, 504);
  tmp->setTile(688, 176, 48, 48);
  _list.push_back(tmp);
  _list.push_back(new Entity(tmp, 1056, 505));

  printTrace("Terrain: создание центрального острова");
  _list.push_back(new Entity(tile, 64 * 2, 112 * 2, 320, 496, 64, 112, 320, 32));
  _list.push_back(new Entity(tile, 16 * 2, 112 * 2, 448, 496, 16, 112, 400, 32));

  /* сталактиты */
  tmp = new Entity(tile, 16 * 2, 32 * 2, 480, 656, 16, 32, 368, 112);
  _list.push_back(tmp);
  for (int i = 1; i < 11; i++)
  {
    Entity *t = new Entity(tmp, 480 + 32 * i, 656);

    if (i == 2 || i == 6 || i == 8 || i == 9) t->setTile(400, 112, 16, 32);

    _list.push_back(t);
  }

  _list.push_back(new Entity(tile, 32 * 2, 64 * 2, 480, 464, 32, 64, 144, 96));
  _list.push_back(new Entity(tile, 16 * 2, 32 * 2, 544, 496, 16, 32, 320, 176));
  _list.push_back(new Entity(tile, 48 * 2, 48 * 2, 576, 496, 48, 48, 192, 176));
  _list.push_back(new Entity(tile, 32 * 2, 48 * 2, 672, 496, 32, 48, 464, 240));
  _list.push_back(new Entity(tile, 16 * 2, 32 * 2, 736, 496, 16, 32, 320, 176));
  _list.push_back(new Entity(tile, 16 * 2, 32 * 2, 768, 496, 16, 32, 352, 176));
  _list.push_back(new Entity(tile, 16 * 2, 32 * 2, 800, 496, 16, 32, 480, 176));
  _list.push_back(new Entity(tile, 64 * 2, 112 * 2, 832, 496, 64, 112, 432, 32));
}
