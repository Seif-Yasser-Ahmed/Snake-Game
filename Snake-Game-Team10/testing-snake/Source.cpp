// Source.cpp
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

/*-------------------Source.cpp------------------------

 This cpp file defines the GUI and the 'main' of the snake game.

// Source.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
----------------------------------------------------------------*/

#include "Game.h"
#include "raylib.h"

#pragma once
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void) {

    // Initialization
    //---------------------------------------------------------
    const int cellsize = 30;
    const int cellcount = 25;
    Color green = { 205, 205, 204,25 };        //background color
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  //for resizing the screen
    InitWindow(2*60+cellsize*cellcount, 2 * 60 + cellsize * cellcount, "Spicy Snake Game");
    SetWindowMinSize(cellsize*cellcount, cellsize * cellcount);
    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    Game game = Game();
    game.btnAction = 0;
    int offsetWidth = GetScreenWidth() - cellsize * cellcount;
    int offsetHeight = GetScreenHeight() - cellsize * cellcount;

    //----------------------------------------------------------
    //---PlaySound(game.welcomeSound);
    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Draw
        //-----------------------------------------------------
        int monitorWidth = GetMonitorWidth(0);
        int monitorHeight = GetMonitorHeight(0);
        BeginDrawing();
        ClearBackground(LIGHTGRAY);          //coloring the background
        game.duringGameScreen();
        EndDrawing();
        //-----------------------------------------------------
    }


    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();                          // Close window and OpenGL context
    //----------------------------------------------------------
    return 0;
}