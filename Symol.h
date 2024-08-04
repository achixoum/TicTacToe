//
// Created by Αχιλλέας on 4/2/2024.
//

#ifndef PROJECTS_SYMOL_H
#define PROJECTS_SYMOL_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Symbol
{
private:
    //the rectangle in which we are going to texture our symbol
    SDL_Rect O_Rectangle;
    //texture that use to draw the symbol
    SDL_Texture* O_Texture;
public:
    //the constructor draws the symbol to the board
    Symbol();
    Symbol(SDL_Renderer*& renderer,const char* FileName);
    ~Symbol();
    void Render_symbol(SDL_Renderer*& renderer);
    void SetRectProperties(int x, int y, uint16_t width, uint16_t height);
    int GetX();
    int GetY();
};

#endif //PROJECTS_SYMOL_H
