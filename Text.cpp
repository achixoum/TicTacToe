#include "Text.h"

Text::Text()
{
    text_font = nullptr;
    text_texture = nullptr;
    text_surface = nullptr;
}
Text::~Text()
{
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(text_font);
}

Text::Text(SDL_Renderer*& renderer, const char* FileName)
{
    text_texture = nullptr;
    text_surface = nullptr;
    text_font = TTF_OpenFont(FileName,1440);
    if (!text_font)
    {
        std::cerr<<"Couldn't' load font"<<std::endl;
        exit(1);
    }
}
void Text::SetText(const char* text, uint8_t red, uint8_t blue, uint8_t green)
{
    text_surface = TTF_RenderText_Solid(text_font,text,{red,blue,green});
}

void Text::SetTexture(SDL_Renderer*& renderer)
{
    if (text_texture)
    {
        SDL_DestroyTexture(text_texture);
        text_texture = nullptr;
    }
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_FreeSurface(text_surface);
    text_surface = nullptr;

}

void Text::SetRectProperties(int x, int y, uint16_t w, uint16_t h)
{
    text_rect.x = x;
    text_rect.y = y;
    text_rect.w = w;
    text_rect.h = h;
}
void Text::RenderText(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer,text_texture,nullptr,&text_rect);
}