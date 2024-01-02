//
// Food.h
// Food class to generate food positions
//
// Created                  on 28/11/2023  "dd/mm/yyyy"
// Updated by Seif Yasser   on 28/11/2023
// Updated by Ali Tarek     on 28/11/2023
// Updated by Gaser Zaghlol on 28/11/2023
// Updated by Arwa Faisal   on 29/11/2023 
/*-------------------Food.h------------------------

 This Header line defines the data class Food for processing Food objects.

 Basic operations are:
 ---------------------------------------------------
 Constructor
 Destructor
 Draw:               Draws the snake on GUI
 GetRandomPosition   generates random position PosX & PosY for object food
---------------------------------------------------*/

#include <iostream>
#include "raylib.h"
using namespace std;

#pragma once

#ifndef FOOD_H
#define FOOD_H
class Food {
public:

    //------- Food data members
    int PosX;
    int PosY;
    Texture2D texture;
    const int cellsize = 30;
    const int cellcount = 25;
    int offsetWidth = GetScreenWidth() - cellsize * cellcount;
    int offsetHeight = GetScreenHeight() - cellsize * cellcount;

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


    /****** get new random position operation ******/
    void GetRandomPosition() {
        PosX = rand() % ((GetScreenWidth() - offsetWidth - offsetWidth + 1)/30)+ offsetWidth/30;
        PosY =rand() % ((GetScreenHeight() - offsetHeight - offsetHeight + 1) / 30) + offsetHeight / 30;
    }


}; //------- End of Food class
#endif
