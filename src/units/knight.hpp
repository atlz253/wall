#include "unit.hpp"

class Knight final : public Unit
{
private:
    int _frame = 0; // Текущий кадр
    int _frameCount = 0; // Счетчик обновления текстуры
    int _animationSpeed = 5; // Скорость анимации
    bool _isRuning = true; // Перемещается ли персонаж?
public:
    Knight(int x = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void process(Unit *next) override;

    /*
        Получение точки затылка юнита
    */
    int getBack(void) override;

    /*
        Получение лицевой точки юнита
    */
    int getFront(void) override;

    ~Knight();
};