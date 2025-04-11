# include <iostream>
# include "TicTacToe.h"
# include "Symbol.h"
# include "Text.h"
# include "Button.h"
# include <SDL.h>

using namespace std;

int main(int argc, char* argv[])
{
    //initializing the all subsystems for our program(e.t.c video...)
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
        SDL_GetError();

    //initialize ttf and image library
    if (TTF_Init() == -1)
    {
        cerr<<"SDL_Init Error: "<<TTF_GetError()<<endl;
        SDL_Quit();
        return 1;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2_ttf initialized successfully");
    IMG_Init(IMG_INIT_PNG);

    //create a pointer type window for our window application
    SDL_Window* window;

    //this function returns a pointer and creates a window for our platform
    //the parameters are title x,y(the position on our screen) the width and height of the window and a flag of its shown
    window = SDL_CreateWindow("TicTacToe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,800,SDL_WINDOW_SHOWN);

    //create renderer
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* overlay = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 800, 800);
    SDL_SetRenderTarget(renderer, overlay);
    Button startButton(renderer,"./images/PlayButton.png",250,100);
    startButton.SetRectProperties(200,600,200,100);
    Button startButton2(renderer, "./images/PlayButton.png",250,100);
    startButton2.SetRectProperties(405, 600, 200, 100);
    Text StartText(renderer,"./fonts/Luna.ttf");
    StartText.SetText("TicTacToe", 20, 20, 20);
    StartText.SetTexture(renderer);
    StartText.SetRectProperties(0,700,800,100);
    Symbol StartImage(renderer,"./images/game-944386_1280.jpg");
    StartImage.SetRectProperties(0,0,800,600);

    //SDL_Texture *overlay2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);
    Button X(renderer, "./images/Xbutton.png",144,140);
    Button O(renderer, "./images/Obutton.png",136,130);
    X.SetRectProperties((800-500)/2,(800-500)/2+180,170,130);
    O.SetRectProperties((800-500)/2+250,(800-500)/2+180,170,130);
    Text chooseText(renderer,"./fonts/Luna.ttf");
    chooseText.SetText("Select symbol", 20, 20, 20);
    chooseText.SetTexture(renderer);

    string symbol;
    bool GameIsRunning2;
    bool GameIsRunning;
    bool start = true;
    while (start)
    {
        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);
        //we create a structure for our events
        SDL_Event event;
        //loop for the queue of the events tha happening every time we are dequeing the event that happened
        while (SDL_PollEvent(&event))
        {
            startButton.Update(x,y,257);
            startButton2.Update(x,y,257);
            X.Update(x,y,144);
            O.Update(x,y,136);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(startButton.IsSelected() && !GameIsRunning2) {
                    start = false;
                    GameIsRunning = true;
                }
                if (startButton2.IsSelected() && !GameIsRunning2) {
                    GameIsRunning2 = true;
                    chooseText.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                    chooseText.SetText("Select symbol", 20, 20, 20);
                    chooseText.SetTexture(renderer);
                }
                if (X.IsSelected()) {
                    start = false;
                    symbol = "X";
                }
                else if (O.IsSelected()){
                    start = false;
                    symbol = "O";
                }
            }
            if(event.type==SDL_QUIT)
            {
                // if the event is quit the stop the game
                start = false;
                GameIsRunning = false;
                GameIsRunning2 = false;
                break;
            }
        }
        // Clear the texture with a semi-transparent color (e.g., black with 50% opacity)
        SDL_SetRenderDrawColor(renderer,230, 223, 211,SDL_ALPHA_OPAQUE);  // RGBA

        if (GameIsRunning2) {
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer,overlay);
            SDL_SetRenderDrawColor(renderer, 230, 223, 211, SDL_ALPHA_OPAQUE); // Black with 0 alpha
            SDL_RenderClear(renderer);
            SDL_Rect rectangle= {(800-500)/2-50,(800-500)/2+50,600,300};
            SDL_SetRenderTarget(renderer, nullptr);
            SDL_RenderCopy(renderer, overlay, nullptr, &rectangle);
            X.RenderButton(renderer);
            O.RenderButton(renderer);
            chooseText.RenderText(renderer);
        }
        else {
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, nullptr);
            SDL_RenderCopy(renderer, overlay, nullptr, nullptr);
            startButton.RenderButton(renderer);
            startButton2.RenderButton(renderer);
            StartImage.Render_symbol(renderer);
            StartText.RenderText(renderer);
        }
        // Present the renderer
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(overlay);
    //SDL_DestroyTexture(overlay2);


    Symbol image(renderer, "./images/Tic-tac-toe.bmp");
    image.SetRectProperties(0,0,800,600);

    Text text1(renderer,"./fonts/Luna.ttf");
    text1.SetText("NOW PLAYING: X", 20, 20, 20);
    text1.SetTexture(renderer);
    text1.SetRectProperties(0,650,500,100);

    Button quit(renderer,"./images/QuitButton.png",250,100);
    quit.SetRectProperties(-800,0,200,100);
    Button reset(renderer,"./images/ResetButton.png",250,100);
    Button playAgain(renderer,"./images/PlayAgainButton.png",250,100);
    SDL_Texture* overlay1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 500, 500);
    // Render the texture onto the renderer

    //symbols of the two players(computer-human)
    string player1,player2;
    //player2 = symbol;
    int j;
    BOARD board2;
    BOARD best;
    player1 = symbol == "X"?"O" : "X";
    player2 = symbol == "X"?"X" : "O";
    j = symbol == "X"?1 : 0;
    board2.setValue(player1=="X");
    bool flag2 = false;
    int g;
    while (GameIsRunning2)
    {
        int x,y;
        Uint32 buttons;
        //we create a structure for our events
        SDL_Event event;
        if (j % 2 == 0 && !flag2) {
            if (j == 0) {
                board2.placeSymbol(renderer, ("./images/" + player1 + ".png").c_str(), player1,0, 0);
            }
            else {
                board2.miniMax(10, true,player1,player2, board2, &best);
                board2.placeSymbol(renderer, ("./images/" + player1 + ".png").c_str(), player1, best.getX(), best.getY());
            }
            text1.SetText(("NOW PLAYING: "+player2).c_str(), 20, 20, 20);
            text1.SetTexture(renderer);
            text1.SetRectProperties(0,650,500,100);
            if (board2.checkForWinner(player1)) {
                playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                text1.SetText((player1+" WON!!!").c_str(), 20, 20, 20);
                text1.SetTexture(renderer);
                text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                flag2 = true;
            }
            j++;
        }
        //loop for the queue of the events tha happening every time we are dequeing the event that happened
        while (SDL_PollEvent(&event))
        {
            buttons = SDL_GetMouseState(&x, &y);
            if (!flag2)
                reset.Update(x,y,257);
            playAgain.Update(x,y,257);
            quit.Update(x,y,257);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                board2.setX(x);
                board2.setY(y);
                if (!flag2) {
                    if (board2.checkBoundaries()) {
                        if (board2.HasSymbol()) {
                            if (!board2.checkColor(renderer)) {
                                if (j % 2 == 1){
                                    board2.placeSymbol(renderer, ("./images/" + player2 + ".png").c_str(), player2,-1,-1);
                                    text1.SetText(("NOW PLAYING: "+player1).c_str(), 20, 20, 20);
                                    text1.SetTexture(renderer);
                                    text1.SetRectProperties(0,650,500,100);
                                    if (board2.checkForWinner(player2)) {
                                        playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                                        quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                                        text1.SetText((player2+" WON!!!").c_str(), 20, 20, 20);
                                        text1.SetTexture(renderer);
                                        text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                                        flag2 = true;
                                    }
                                    j++;
                                }
                            }
                        }
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (reset.IsSelected() && !flag2)
                {
                    board2.DestroyBoard();
                    j=player2 == "X"?1:0;
                    text1.SetText("NOW PLAYING: X", 20, 20, 20);
                    text1.SetTexture(renderer);
                    text1.SetRectProperties(0,650,500,100);
                }
                if (playAgain.IsSelected() && flag2)
                {
                    board2.DestroyBoard();
                    j =player2 == "X"?1:0;
                    text1.SetText("NOW PLAYING: X", 20, 20, 20);
                    text1.SetTexture(renderer);
                    text1.SetRectProperties(0,650,500,100);
                    quit.SetRectProperties(-800,0,200,100);
                    playAgain.SetRectProperties(-800,100,200,100);
                    flag2 = false;
                }
                if (quit.IsSelected()) {
                    GameIsRunning2 = false;
                    break;
                }
            }
            if (j==9 && !flag2)
            {
                playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                text1.SetText("DRAW", 20, 20, 20);
                text1.SetTexture(renderer);
                text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                flag2 = true;
            }
            if(event.type==SDL_QUIT)
            {
                // if the event is quit the stop the game
                GameIsRunning2 = false;
                break;
            }
        }
        //first we set the color for the screen and then draw other objects
        SDL_SetRenderDrawColor(renderer,255, 255, 224,SDL_ALPHA_OPAQUE);
        //render clear and draw the screen
        SDL_RenderClear(renderer);

        // Render scene normally
        image.Render_symbol(renderer);
        text1.RenderText(renderer);
        reset.RenderButton(renderer);
        board2.RenderSymbol(renderer);

        // Render the blurred texture to the screen
        if (flag2)
        {
            SDL_SetRenderTarget(renderer,overlay1);
            SDL_SetRenderDrawColor(renderer, 255, 255, 224, 0); // Black with 0 alpha
            SDL_RenderClear(renderer);
            SDL_Rect rectangle1= {(800-500)/2-50,(800-500)/2+50,600,300};
            SDL_SetRenderTarget(renderer, nullptr);
            SDL_RenderCopy(renderer, overlay1, nullptr, &rectangle1);
            playAgain.RenderButton(renderer);
            quit.RenderButton(renderer);
            text1.RenderText(renderer);
        }
        SDL_RenderPresent(renderer);
    }

    j = 0;
    bool flag = false;
    BOARD board;
    while (GameIsRunning)
    {
        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);
        //we create a structure for our events
        SDL_Event event;
        //loop for the queue of the events tha happening every time we are dequeing the event that happened
        while (SDL_PollEvent(&event))
        {
            if (!flag)
                reset.Update(x,y,257);
            playAgain.Update(x,y,257);
            quit.Update(x,y,257);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                board.setX(x);
                board.setY(y);
                if (!flag) {
                    if (board.checkBoundaries()) {
                        if (board.HasSymbol()) {
                            if (!board.checkColor(renderer)) {
                                if (j % 2 == 0) {
                                    board.placeSymbol(renderer, "./images/O.png", "O", -1, -1);
                                    text1.SetText("NOW PLAYING: X", 20, 20, 20);
                                    text1.SetTexture(renderer);
                                    text1.SetRectProperties(0,650,500,100);
                                } else {
                                    board.placeSymbol(renderer, "./images/X.png", "X", -1, -1);
                                    text1.SetText("NOW PLAYING: O", 20, 20, 20);
                                    text1.SetTexture(renderer);
                                    text1.SetRectProperties(0,650,500,100);
                                }
                                if (j % 2 == 0) {
                                    if (board.checkForWinner("O")) {
                                        playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                                        quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                                        text1.SetText("O WON!!!", 20, 20, 20);
                                        text1.SetTexture(renderer);
                                        text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                                        flag = true;
                                    }
                                } else if (board.checkForWinner("X")) {
                                    playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                                    quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                                    text1.SetText("X WON!!!", 20, 20, 20);
                                    text1.SetTexture(renderer);
                                    text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                                    flag = true;
                                }
                                j++;
                            }
                        }
                    }
                }
                if (reset.IsSelected() && !flag)
                {
                    board.DestroyBoard();
                    j=0;
                    text1.SetText("NOW PLAYING: O", 20, 20, 20);
                    text1.SetTexture(renderer);
                    text1.SetRectProperties(0,650,500,100);
                }
                if (playAgain.IsSelected() && flag)
                {
                    board.DestroyBoard();
                    j=0;
                    text1.SetText("NOW PLAYING: O", 20, 20, 20);
                    text1.SetTexture(renderer);
                    text1.SetRectProperties(0,650,500,100);
                    quit.SetRectProperties(-800,0,200,100);
                    playAgain.SetRectProperties(-800,100,200,100);
                    flag = false;
                }
                if (quit.IsSelected()) {
                    GameIsRunning = false;
                    break;
                }
            }
            if (j==9 && !flag)
            {
                playAgain.SetRectProperties((800-500)/2+150,(800-500)/2+150,200,100);
                quit.SetRectProperties((800-500)/2+150,(800-500)/2+250,200,100);
                text1.SetText("DRAW", 20, 20, 20);
                text1.SetTexture(renderer);
                text1.SetRectProperties((800-500)/2-50,(800-500)/2+50,500,100);
                flag = true;
            }
            if(event.type==SDL_QUIT)
            {
                // if the event is quit the stop the game
                GameIsRunning = false;
                break;
            }
        }
        //first we set the color for the screen and then draw other objects
        SDL_SetRenderDrawColor(renderer,255, 255, 224,SDL_ALPHA_OPAQUE);
        //render clear and draw the screen
        SDL_RenderClear(renderer);

        // Render scene normally
        image.Render_symbol(renderer);
        text1.RenderText(renderer);
        reset.RenderButton(renderer);
        board.RenderSymbol(renderer);

        // Render the blurred texture to the screen
        if (flag)
        {
            SDL_SetRenderTarget(renderer,overlay1);
            SDL_SetRenderDrawColor(renderer, 255, 255, 224, 0); // Black with 0 alpha
            SDL_RenderClear(renderer);
            SDL_Rect rectangle= {(800-500)/2-50,(800-500)/2+50,600,300};
            SDL_SetRenderTarget(renderer, nullptr);
            SDL_RenderCopy(renderer, overlay1, nullptr, &rectangle);
            playAgain.RenderButton(renderer);
            quit.RenderButton(renderer);
            text1.RenderText(renderer);
        }
        SDL_RenderPresent(renderer);
    }
    //destroy the allocated memory(textures,renderers,surfaces)
    SDL_DestroyTexture(overlay1);
    SDL_DestroyRenderer(renderer);
    //destroy the pointer of our window
    SDL_DestroyWindow(window);
    //quit sdl
    SDL_Quit();

    return 0;
}
