#include "print.hpp"
#include "texture.hpp"
#include "textureManager.hpp"

TextureManager::TextureManager()
{
    printTrace("Инициализация менеджера текстур");
}

Texture *&TextureManager::key(std::string name)
{
    _iterator = _dict.find(name);

    if (_iterator->first != name)
        _dict[name] = nullptr; // на всякий случай создаем пару ключ:значение

    return _dict[name];
}

TextureManager::~TextureManager()
{
    for (_iterator = _dict.begin(); _iterator != _dict.end(); _iterator++)
        delete _iterator->second;
}