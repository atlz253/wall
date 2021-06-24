#include "globals.hpp"

Gui *gui = nullptr;
Renderer *renderer = new Renderer();  // TODO: инициализация в классе Wall
EventSubSystem *events = new EventSubSystem();
TextureManager *textures = new TextureManager();
Font *font = new Font();
SdlWindow *window = nullptr;
Action *action = nullptr;
std::string *p1 = new std::string, *p2 = new std::string;
