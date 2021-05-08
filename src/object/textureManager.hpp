#include <map>
#include <string>

class Texture;

/*
    Объект хранит в себе все загруженные текстуры в формате ключ:значение
*/
class TextureManager final
{
private:
    std::map<std::string, Texture*> _dict; // контейнер текстур
    std::map<std::string, Texture*> :: iterator _iterator; // итератор для работы с контейнером
public:
    TextureManager();

    /*
        Получение объекта текстуры по ключу
    */
    Texture *&key(std::string name);

    ~TextureManager();
};