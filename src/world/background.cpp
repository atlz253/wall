#include "print.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "background.hpp"

class Clouds : public Entity
{
private:
    int _startPosition;

public:
    Clouds(Renderer *renderer, std::string path, int w, int h, int x = 0, int y = 0) //FIXME: что за фигня с конструкторами??? Я не смогу использовать конструкторы из Entity?!
    {
        setSize(w, h);
        setPosition(x, y);
        _startPosition = x;
        _loadTexture(renderer, path);
    }

    void process(void) override
    {
        _geometry->x += 1;
    }

    void renderer(void) override
    {
        if (_geometry->x <= 1280)
            Entity::renderer();

        if (_geometry->x - _startPosition == 1088)
            _geometry->x = _startPosition;
    }
};

Background::Background(Renderer *renderer)
{
    Entity *p;

    printTrace("Background: инициализация неба");
    p = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/sky.png", 124, 608);
    _list.push_back(p);
    for (int i = 1; i < 11; i++)
        _list.push_back(new Entity(p, i * 124));

    printTrace("Background: инициализация моря");
    p = new Entity(renderer, "res/Magic-Cliffs-Environment/PNG/sea.png", 124, 192, 0, 608);
    _list.push_back(p);
    for (int i = 1; i < 11; i++)
        _list.push_back(new Entity(p, i * 124, 608));

    printTrace("Background: инициализация облаков");
    // p = new Clouds(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png", 1088, 472, 0, 136);
    // _list.push_back(p);
    // _list.push_back(new Clouds(p, -1088, 136));
    // _list.push_back(new Clouds(p, 1088, 136));
    _list.push_back(new Clouds(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png", 1088, 472, 0, 136));
    _list.push_back(new Clouds(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png", 1088, 472, -1088, 136));
    _list.push_back(new Clouds(renderer, "res/Magic-Cliffs-Environment/PNG/clouds.png", 1088, 472, 1088, 136));
}