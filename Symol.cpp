#include "Symol.h"
#include "ResourceManager.h"

Symbol::Symbol() {
    O_Texture = nullptr;
}

Symbol::Symbol(SDL_Renderer*& renderer, const char* FileName)
{
    SDL_Surface* symbol = ResourceManager::GetInstance().GetSurface(const_cast<char *>(FileName));
    O_Texture = SDL_CreateTextureFromSurface(renderer,symbol);
    O_Rectangle = {0,0,0,0};
}

Symbol::~Symbol()
{
    SDL_DestroyTexture(O_Texture);
}

void Symbol::SetRectProperties(int x, int y, uint16_t width, uint16_t height)
{
    O_Rectangle.w = width;
    O_Rectangle.h = height;
    this->O_Rectangle.x = x;
    this->O_Rectangle.y = y;
}

int Symbol::GetX()
{
    return O_Rectangle.x;
}
int Symbol::GetY()
{
    return O_Rectangle.y;
}

void Symbol::Render_symbol(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer, O_Texture, nullptr, &O_Rectangle);
}