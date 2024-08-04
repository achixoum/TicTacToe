#include "Button.h"

Button::Button(SDL_Renderer *renderer, const char *fileName) {
    SDL_Surface* symbol = ResourceManager::GetInstance().GetSurface(const_cast<char *>(fileName));
    ButtonTexture = SDL_CreateTextureFromSurface(renderer,symbol);

    SourceRect = {0,0,250,100};

    DestRect.w = 200;
    DestRect.h = 100;
    DestRect.x = 600;
    DestRect.y = 650;

    isSelected = false;
}

Button::~Button()
{
    SDL_DestroyTexture(ButtonTexture);
}

void Button::SetRectProperties(int x, int y, uint16_t w, uint16_t h)
{
    DestRect.w = w;
    DestRect.h = h;
    DestRect.x = x;
    DestRect.y = y;
}

bool Button::withinBounds(int x, int y)
{
    // Too far left
    if (x < DestRect.x) return false;
    // Too far right
    if (x > DestRect.x + DestRect.w) return false;
    // Too high
    if (y < DestRect.y) return false;
    // Too low
    if (y > DestRect.y + DestRect.h) return false;
    // Within bounds
    return true;
}

void Button::Update(int x, int y)
{
    if (withinBounds(x,y))
    {
        isSelected = true;
        SourceRect.x = 257;
    }
    else
    {
        isSelected = false;
        SourceRect.x = 0;
    }
}

void Button::RenderButton(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer,ButtonTexture,&SourceRect,&DestRect);
}

bool Button::IsSelected()
{
    return isSelected;
}