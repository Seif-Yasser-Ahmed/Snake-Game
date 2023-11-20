// Snake-Game-Team10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Snake.h"
#include "raylib.h"

#pragma once
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

Color green = { 173,204,96,255 };
Color darkgreen = { 43,51,24,255 };
int cellsize = 30;
int cellcount = 50;

/******** Class Food for  ********/
class Food {
public:
    int PosX = rand() % cellsize;
    int PosY = rand() % cellsize;
    Texture2D texture;

    Food() {

        Image image = LoadImage("Graphics/Snake.png");
        ImageResizeNN(&image, 30, 30);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture,PosX*cellsize,PosY*cellsize,WHITE);
    }
};
//------- End of Food class


int main(void) {

    // Initialization
   //---------------------------------------------------------

    const int screenWidth = 1000;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Bouncing Ball");

    Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;

    Snake snake=Snake();
    Food food;

    bool pause = 0;
    int framesCounter = 0;

    SetTargetFPS(20);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        //snake.Draw();
        if (!pause)
        {
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Check walls collision for bouncing
            if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
        }
        else framesCounter++;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();
        if(snake.eventTriggered(0.2)){
            snake.update();
        }
        

        if (IsKeyPressed(KEY_RIGHT)&&snake.x!=-1) {
            snake.x = 1;
            snake.y = 0;

        }
        if (IsKeyPressed(KEY_LEFT) && snake.x != 1) {
            snake.x = -1;
            snake.y = 0;
        }if (IsKeyPressed(KEY_UP) && snake.y != 1) {
            snake.x = 0;
            snake.y = -1;
        }if (IsKeyPressed(KEY_DOWN) && snake.y != -1) {
            snake.x = 0;
            snake.y = 1;
        }
        

        ClearBackground(green); //coloring the background
        //snake.Draw();
        food.Draw();
        snake.Draw();
        DrawCircleV(ballPosition, (float)ballRadius, darkgreen);
        //DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);

        // On pause, we draw a blinking message
        //if (pause && ((framesCounter / 30) % 2)) DrawText("PAUSED", 350, 200, 30, GRAY);
        if (pause) DrawText("paused", 438, 356, 30, GRAY);

        DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}