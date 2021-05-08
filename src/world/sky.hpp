#include "entity.hpp"

class Sky final : public Entity
{
protected:
    void _renderer(SDL_Renderer *renderer) override;

public:
    Sky(Texture *texture);
};