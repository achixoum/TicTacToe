#include <iostream>
#include "TicTacToe.h"

BOARD::BOARD()
{
    for(int i=0;i<9;i++)
    {
        array[i] = " ";
    }
    map = {
        {1,{254/2,192/2}}, {2,{203/2+254+46,192/2}}, {3,{251/2+503+46,192/2}},
        {4,{254/2,153/2+192+36}}, {5,{203/2+254+46,153/2+192+36}}, {6,{251/2+503+46, 153/2+192+36}},
        {7,{254/2,183/2+381+36}}, {8,{203/2+254+46,183/2+381+36}}, {9,{251/2+503+46,183/2+381+36}}
    };
}

void BOARD::setX(int x)
{
    this->x = x;
}
void BOARD::setY(int y)
{
    this->y = y;
}
int BOARD::getX()
{
    return x;
}
int BOARD::getY()
{
    return y;
}

bool BOARD::checkBoundaries()
{
    return x<800 && y<600;
}

bool BOARD::checkForWinner(const string& symbol)
{
    int count1 = 0;
    int count2 = 0;
    for(int i=0;i<3;i++)
    {
        int count3 = 0;
        int count4 = 0;
        for(int j=0;j<3;j++)
        {
            if (array[i*3+j]==symbol)
                count3++;
            if (array[j*3+i]==symbol)
                count4++;
            if (i==j && array[i*3+j]==symbol)
                count1++;
            if (i+j==2 && array[i*3+j]==symbol)
                count2++;
        }
        if (count3==3 || count4==3)
            return true;
    }
    if (count1==3 || count2==3)
        return true;
    return false;
}

int BOARD::checkCordinates()
{
    if (x<254 && y<192)
        return 1;
    if (x<503 && y<192)
        return 2;
    if (x<800 && y<192)
        return 3;
    if (x<254 && y<381)
        return 4;
    if (x<503 && y<381)
        return 5;
    if (x<800 && y<381)
        return 6;
    if (x<254 && y<600)
        return 7;
    if (x<503 && y<600)
        return 8;
    if (x<800 && y<600)
        return 9;
}

bool BOARD::HasSymbol()
{
    return array[checkCordinates()-1] == " ";
}

bool BOARD::isMouseOverColor(SDL_Renderer* renderer, Uint32 targetColor) {

    // Get the color of the pixel under the mouse cursor
    Uint32 pixelColor = getPixelColor(renderer, x, y);
    // Compare the pixel color with the target color
    return pixelColor == targetColor;
}

// Function to get the color of a pixel at (x, y)
Uint32 BOARD::getPixelColor(SDL_Renderer* renderer, int X, int Y) {
    // Define a pixel array to hold the pixel data
    Uint32 pixel = 0;

    SDL_Rect rectangle;
    rectangle.x = X;
    rectangle.y = Y;
    rectangle.w = 1;
    rectangle.h = 1;

    // Use SDL_RenderReadPixels to read the pixel data
    if (SDL_RenderReadPixels(renderer, &rectangle, SDL_PIXELFORMAT_ARGB8888, &pixel, sizeof(Uint32)) != 0) {
        std::cerr << "SDL_RenderReadPixels Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    return pixel;
}

int BOARD::checkColor(SDL_Renderer* renderer)
{
    return isMouseOverColor(renderer,getPixelColor(renderer, 162, 213));
}

void BOARD::placeSymbol(SDL_Renderer* renderer, const char* FileName, const string& symbol)
{
    int a = checkCordinates();
    shared_ptr<Symbol> rect = make_shared<Symbol>(renderer, FileName);
    symbols1.push_back(rect);
    symbols1.back()->SetRectProperties(map[a].first-124, map[a].second-97, 266, 200);
    array[a-1] = symbol;
}

void BOARD::RenderSymbol(SDL_Renderer*& renderer)
{
    for (auto & i : symbols1) {
        i->Render_symbol(renderer);
    }
}

void BOARD::DestroyBoard()
{
    for(int i=0;i<9;i++)
    {
        array[i] = " ";
    }
    symbols1.clear();
}
