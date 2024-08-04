#ifndef PROJECTS_TEXT_H
#define PROJECTS_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>

class Text
{
private:
    SDL_Rect text_rect;
    SDL_Surface* text_surface;
    SDL_Texture* text_texture;
    TTF_Font* text_font;
    std::unordered_map<char*, TTF_Font*> fonts;
public:
    Text();
    ~Text();
    Text(SDL_Renderer*& renderer, const char* FileName);
    void SetText(const char* text, uint8_t red, uint8_t blue, uint8_t green);
    void SetTexture(SDL_Renderer*& renderer);
    void SetRectProperties(int x, int y, uint16_t w, uint16_t h);
    void RenderText(SDL_Renderer*& renderer);
};

#endif //PROJECTS_TEXT_H
