#include "window.hpp"

/*
    Объект данного класса хранит в себе основные компоненты игры.

    Большинство игр состоит из 5 основных функций:
    1. Функция инициализации.
    2. Обработчик событий.
    3. Игровой цикл.
    4. Отрисовка сцен.
    5. Очистка памяти.
*/
class Main final
{
private:
    SdlWindow *_window;

    /*
        Игровой цикл

        Обрабатывает все обновления игры
    */
    void _gameLoop(void);

public:
    /*
        Инициализация игры

        Обрабатывает загрузку всех данных
    */
    Main();

    /*
        Запуск игры
    */
    int run(void);

    /*
        Очистка памяти

        Удаляет все загруженные ресурсы из ОЗУ
    */
    ~Main();
};