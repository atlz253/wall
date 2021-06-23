#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <map>
#include <string>

typedef struct SDL_Texture SDL_Texture;

/*
    Объект хранит в себе все загруженные текстуры в формате ключ:значение
*/
class TextureManager final
{
 private:
  std::map<std::string, SDL_Texture *> _dict;                // контейнер текстур
  std::map<std::string, SDL_Texture *>::iterator _iterator;  // итератор для работы с контейнером
 public:
  TextureManager();

  /*
      Загрузка текстуры
  */
  void loadTexture(std::string path);
  void loadTexture(std::string name, std::string path); // TODO: убрать

  /*
      Получение объекта текстуры по ключу
  */
  SDL_Texture *&key(std::string name);

  ~TextureManager();
};

#endif
