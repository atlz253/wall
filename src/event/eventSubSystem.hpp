typedef union SDL_Event SDL_Event;

/*
    Подсистема обработки событий SDL
*/
class EventSubSystem final
{
private:
    SDL_Event *_event; // Обработчик событий
public:
    EventSubSystem();

    /*
        Проверка новых игровых событий
    */
    bool checkEvents(void);

    ~EventSubSystem();
};