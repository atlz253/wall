#include "entity.hpp"

class Renderer;
class TextureManager;

class Background final : public Entity
{
private:
    Texture *_seaTexture = nullptr;   // Текстура моря
    SDL_Rect *_seaGeometry = nullptr; // Геометрия сущности

    int _cloudsAnimation = 0;            // Переменная для анимации облаков
    Texture *_cloudsTexture = nullptr;   // Текстура облаков
    SDL_Rect *_cloudsGeometry = nullptr; // Геометрия облаков

protected:
    void _renderer(SDL_Renderer *renderer, Texture *texture, SDL_Rect *geometry) override;

public:
    Background(TextureManager *&textures, Renderer *&renderer);
};