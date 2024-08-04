# include <iostream>
# include "TicTacToe.h"
# include "Symol.h"
# include "Text.h"
# include "Button.h"

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
    else
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
    Button startButton(renderer,"./images/PlayButton.png");
    startButton.SetRectProperties(310,600,200,100);
    Text StartText(renderer,"./fonts/Luna.ttf");
    StartText.SetText("TicTacToe", 20, 20, 20);
    StartText.SetTexture(renderer);
    StartText.SetRectProperties(0,700,800,100);
    Symbol StartImage(renderer,"./images/game-944386_1280.jpg");
    StartImage.SetRectProperties(0,0,800,600);

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
            startButton.Update(x,y);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(startButton.IsSelected()) {
                    start = false;
                    GameIsRunning = true;
                }
            }
            if(event.type==SDL_QUIT)
            {
                // if the event is quit the stop the game
                start = false;
                GameIsRunning = false;
                break;
            }
        }
        // Clear the texture with a semi-transparent color (e.g., black with 50% opacity)
        SDL_SetRenderDrawColor(renderer,230, 223, 211,SDL_ALPHA_OPAQUE);  // RGBA
        SDL_RenderClear(renderer);

        // Reset render target to default (screen)
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_RenderCopy(renderer, overlay, nullptr, nullptr);
        startButton.RenderButton(renderer);
        StartImage.Render_symbol(renderer);
        StartText.RenderText(renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(overlay);

    Symbol image(renderer, "./images/Tic-tac-toe.bmp");
    image.SetRectProperties(0,0,800,600);

    Text text1(renderer,"./fonts/Luna.ttf");
    text1.SetText("NOW PLAYING: O", 20, 20, 20);
    text1.SetTexture(renderer);
    text1.SetRectProperties(0,650,500,100);

    Button quit(renderer,"./images/QuitButton.png");
    quit.SetRectProperties(-800,0,200,100);
    Button reset(renderer,"./images/ResetButton.png");
    Button playAgain(renderer,"./images/PlayAgainButton.png");
    SDL_Texture* overlay1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 500, 500);
    // Render the texture onto the renderer
    int j = 0;
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
                reset.Update(x,y);
            playAgain.Update(x,y);
            quit.Update(x,y);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                board.setX(x);
                board.setY(y);
                if (!flag) {
                    if (board.checkBoundaries()) {
                        if (board.HasSymbol()) {
                            if (!board.checkColor(renderer)) {
                                if (j % 2 == 0) {
                                    board.placeSymbol(renderer, "./images/circle.png", "O");
                                    text1.SetText("NOW PLAYING: X", 20, 20, 20);
                                    text1.SetTexture(renderer);
                                    text1.SetRectProperties(0,650,500,100);
                                } else {
                                    board.placeSymbol(renderer, "./images/X.png", "X");
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
                    flag = false;
                }
                if (quit.IsSelected()) {
                    GameIsRunning = false;
                    break;
                }
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
