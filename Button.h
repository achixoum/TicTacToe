#ifndef PROJECTS_BUTTON_H
#define PROJECTS_BUTTON_H

#include <SDL.h>
#include "ResourceManager.h"

class Button {
private:
    SDL_Rect SourceRect,DestRect;
    SDL_Texture* ButtonTexture;
    bool isSelected;
    bool withinBounds(int x, int y);
public:
    Button(SDL_Renderer* renderer, const char* fileName);
    ~Button();
    void Update(int x, int y);
    void SetRectProperties(int x, int y, uint16_t w, uint16_t h);
    void RenderButton(SDL_Renderer*& renderer);
    bool IsSelected();
};


#endif //PROJECTS_BUTTON_H
