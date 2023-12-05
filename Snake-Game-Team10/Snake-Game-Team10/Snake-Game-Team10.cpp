// Snake-Game-Team10.cpp
// Snake Game using linked-list
// 
//*******************************************
// 
// Team Members:
// ------------------------------------------
// Seif Yasser          21P0102
// Ali Tarek            21P0123
// Gaser Zaghlol        21P0052
// Arwa Faisal          21P0073
// 
//*******************************************/


/*-------------------Snake-Game-Team10.cpp------------------------

 This cpp file defines the GUI and the 'main' of the snake game.


// Snake-Game-Team10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
----------------------------------------------------------------*/

#include "Snake.h"
#include "raylib.h"
#pragma once

//------------------------------------------------------------------------------------
// Program initializations
//------------------------------------------------------------------------------------

Color green = { 173,204,96,25 };    //background color
int cellsize = 30;                  //size of the cell of the screen
int cellcount = 50;                 // no of cells in the screen
typedef enum GameScreen { LOGO = 0, TITLE,TYPE, GAMEPLAY,GAMEOVER } GameScreen;
bool allowmove;                     // to control inputs from the user
bool modern;                        // to choose between modern and classic game
int gScore = 0;                     // to store the current score of the game
int hScore = 0;                     // to store the high score of the game 


/*************** Class Food ***************/
class Food {
public:

    //------- Food data members
    int PosX;
    int PosY;
    Texture2D texture;

    //------- Food operations

    /****** class Food constructor ******/
    Food() {
        GetRandomPosition();
        Image image = LoadImage("Graphics/Snake.png");
        ImageResizeNN(&image, 30, 30);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    /****** class Food destructor ******/
    ~Food() {
        UnloadTexture(texture);
    }

    /****** draw food on screen operation ******/
    void Draw() {
        DrawTexture(texture, PosX * cellsize, PosY * cellsize, WHITE);
    }

    /****** spawn food operation ******/
    void SpawnFood() {
        GetRandomPosition();
    }

    /****** get new random position operation ******/
    void GetRandomPosition() {
        PosX = rand() % 34;
        PosY = rand() % 30;
    }
};
//------- End of Food class


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {

    // Initialization
   //---------------------------------------------------------
    const int screenWidth = 1020;       
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Spicy Snake Game");
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    bool pause = 0;                     // To pause the game
    int framesCounter = 0;              // frames counter initialization
    GameScreen currentScreen = LOGO;    // first screen of the game
    double difficulty = 0.2;            // speed of the game by changing the event triggered
    Snake snake = Snake();              // Instansiation a snake object
    Food food;                          //constructing the food object
    allowmove = false;                  // to avoid overmoving of the snake

    //----------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        switch (currentScreen) {
        case LOGO: {
            if (IsKeyPressed(KEY_ENTER)|| IsKeyPressed(KEY_SPACE))
            {
                currentScreen = TYPE;
            }
        }break;
        case TYPE: {
            // modern or classic
            if (IsKeyPressed('1')) {
                modern = true;
                currentScreen = TITLE;
            }
            else if (IsKeyPressed('2')) {
                modern = false;
                currentScreen = TITLE;
            }
        
        }break;
        case TITLE: {
            // setting the difficulty
            if (IsKeyPressed('1'))
            {
                difficulty = 0.3;
                currentScreen = GAMEPLAY;
            }
            else if (IsKeyPressed('2')) {
                difficulty = 0.2;
                currentScreen = GAMEPLAY;
            }
            else if (IsKeyPressed('3')) {
                difficulty = 0.1;
                currentScreen = GAMEPLAY;
            }
            else if (IsKeyPressed('4')) {
                difficulty = 0.05;
                currentScreen = GAMEPLAY;
            }
        }break;
        case GAMEOVER: {
            if (IsKeyPressed('1'))
            {
                currentScreen = GAMEPLAY;
            }
            else if (IsKeyPressed('2')) {
                currentScreen = TITLE;
            }
            else if (IsKeyPressed('3')) {
                currentScreen = TYPE;
            }
        }
        case GAMEPLAY: {
        }break;
        default:break;
        }
        
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(green); //coloring the background

        // Screens
        //-----------------------------------------------------
        switch (currentScreen)
        {
        case LOGO: 
        {
            DrawText("WELCOME TO OUR GAME", 150, 80, 60, GRAY);
            DrawText("TEAM 10!", 400, 320, 40, GRAY);
            DrawText("Seif Yasser", 400, 390, 40, GRAY);
            DrawText("Ali Tarek", 400, 440, 40, GRAY);
            DrawText("Gaser Zaghlol", 400, 490, 40, GRAY);
            DrawText("Arwa faisal", 400, 540, 40, GRAY);
            DrawText("21P0102", 800, 390, 40, GRAY);
            DrawText("21P0123", 800, 440, 40, GRAY);
            DrawText("21P0052", 800, 490, 40, GRAY);
            DrawText("21P0073", 800, 540, 40, GRAY);
            DrawText("Press Enter or Space to play", 220, 650, 40, GRAY);
        }break;
        case TYPE: 
        {
            DrawText("Which one do you want to play?", 160, 300, 45, DARKGREEN);
            DrawText("1.Modern      2.Classic", 340, 420, 30, DARKGREEN);
        }break;
        case TITLE:
        {
            DrawText("Spicy Snake Game", 230, 20, 60, DARKGREEN);
            DrawText("Select which difficulty you want", 178, 300, 40, DARKGREEN);
            DrawText("1.Easy    2.Medium    3.Hard  4.Impossible", 297, 400, 20, DARKGREEN);
        } break;
        case GAMEPLAY:
        {  
            if (IsKeyPressed(KEY_SPACE)) pause = !pause; // pausing the game
            if (!pause)
            {
                // ********************** right arrow **********************
                if (IsKeyPressed(KEY_RIGHT) && snake.x != -1&&allowmove) {
                    snake.x = 1;
                    snake.y = 0;
                    allowmove = false;
                }
                // ********************** left arrow **********************
                else if (IsKeyPressed(KEY_LEFT) && snake.x != 1 && allowmove) {
                    snake.x = -1;
                    snake.y = 0;
                    allowmove = false;
                }
                // ********************** up arrow **********************
                else if (IsKeyPressed(KEY_UP) && snake.y != 1 && allowmove) {
                    snake.x = 0;
                    snake.y = -1;
                    allowmove = false;
                }
                // ********************** down arrow **********************
                else if (IsKeyPressed(KEY_DOWN) && snake.y != -1 && allowmove) {
                    snake.x = 0;
                    snake.y = 1;
                    allowmove = false;
                }

                // ********************** event trigger **********************
                if (snake.eventTriggered(difficulty)) {
                    snake.update();
                    allowmove = true;
                }
                // ********************** self & bound collisions **********************
                if (snake.selfCollision()||snake.boundCollision(modern)) {
                    currentScreen = GAMEOVER;
                    gScore = snake.score;
                    if (snake.newHighScore()) {
                        hScore = gScore;
                    }
                    snake.reset();
                    break;
                }
                // ********************** eating food **********************
                if (snake.EatingCheck(food.PosX,food.PosY)) {
                    food.SpawnFood();
                    if (snake.IsSnakeBody(food.PosX,food.PosY)) {
                        food.GetRandomPosition();
                    }
                }
                // ********************** home screen **********************
                if (IsKeyPressed(KEY_ENTER)) {
                    currentScreen = TYPE;
                }
            }
            else if (pause) DrawText("paused", 465, 400, 30, GRAY);             // when pausing the game

            DrawText(TextFormat("%i", snake.score), 100, 100,30, GRAY);         // draw score on screen

            food.Draw();                                                        // drawing the snake
            snake.Draw();                                                       // drawing the snake

        } break;
        case GAMEOVER: 
        {
            DrawText("GAME OVER!", 310, 330, 60, DARKGREEN);
            DrawText("Score: ", 380, 430, 45, DARKGREEN);
            DrawText(TextFormat("%i", gScore), 535, 430, 45, DARKGREEN);
            DrawText("High Score: ", 380, 480, 45, DARKGREEN);
            DrawText(TextFormat("%i", hScore), 645, 480, 45, DARKGREEN);
            DrawText("1.Play again  2.Choose other difficulty   3.change game mood", 120, 560, 28, DARKGREEN);
        }
        default:break;
        }

        EndDrawing();
    //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}
