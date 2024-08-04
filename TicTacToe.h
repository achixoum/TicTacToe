
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Symol.h"

using namespace std;

class BOARD
{
private:
    int x, y;
    string array[9];
    vector<shared_ptr<Symbol>> symbols1;
    unordered_map<int ,pair<int,int>> map;
public:
    BOARD();
    void setX(int x);
    void setY(int x);
    int getX();
    int getY();
    bool checkForWinner(const string& symbol);
    bool HasSymbol();
    bool checkBoundaries();
    int checkCordinates();
    void placeSymbol(SDL_Renderer* renderer, const char* FileName, const string& symbol);
    void RenderSymbol(SDL_Renderer*& renderer);
    int checkColor(SDL_Renderer* renderer);
    Uint32 getPixelColor(SDL_Renderer* renderer, int X, int Y);
    bool isMouseOverColor(SDL_Renderer* renderer, Uint32 targetColor);
    void DestroyBoard();
};

#endif