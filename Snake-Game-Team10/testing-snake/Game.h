//
// Game.h
// Game class to link between Snake and Food classes
//
// Created                  on 28/11/2023  "dd/mm/yyyy"
// Updated by Seif Yasser   on 28/11/2023
// Updated by Ali Tarek     on 28/11/2023
// Updated by Gaser Zaghlol on 28/11/2023
// Updated by Arwa Faisal   on 28/11/2023 
// Updated by Seif Yasser   on 29/11/2023
/*-------------------Game.h------------------------

 This Header line defines the data class Game for processing Snake and Food.

 Basic operations are:
 ---------------------------------------------------
 Constructor
 Draw:               Draws the snake on GUI
 update:             Updates the snake state every frame
 eventTriggered:     Trigger to control the game speed
 beforeGameScreens:  screens responses to user's input before the game starts
 duringGameScreen:   screens UI during the game and controls of the game
 newHighScore:       checks if the player made a new score

---------------------------------------------------*/

#include "Food.h"
#include "Snake.h"
using namespace std;

#pragma once // makes the "Game.h" to be loaded in the memory only one time


#ifndef GAME_H
#define GAME_H
class Game
{
public:
    /************ Function Members *************/

    /********* Class Constructor **********/
    Game();
    ~Game();
    /*-----------------------------------------------------------------
    Construct a Game object

    Precondition: None
    Postcodition: An empty Snake object has been constructed; mySize=0.
    -------------------------------------------------------------------*/


    /****** draw the snake operation ******/
    void Draw();
    /*-----------------------------------------------------------------
    draws the game GUI on the screen

    Precondition: size of the snake to loop on;
    Postcodition: draws the snake on the GUI screen.
    -------------------------------------------------------------------*/


    /****** update the snake operation ******/
    void update();
    /*-----------------------------------------------------------------
    update the game position every frame (60 times per second) in the main loop.

    Precondition: None.
    Postcodition: update every node's and food's position in the game within the time detected by the eventTriggered function.
    -------------------------------------------------------------------*/


    /****** eventTriggered based on time operation ******/
    bool eventTriggered(double interval);
    /*-----------------------------------------------------------------
    check if a specific time has passed like the CLK in the CPU to update the snake position in the GUI

    Precondition: interval of time to trigger after.
    Postcodition:returns true or false based on if the interval specified passed or not.
    -------------------------------------------------------------------*/


    /****** during the game screen operation ******/
    void duringGameScreen();
    /*-----------------------------------------------------------------
    Draws the GUI of each screen of the game while looping in the main after BeginDrawing operation

    Precondition: case of the current screen and inputs from user of the gameplay screen.
    Postcodition: shows the updated snake and food objects each interval 'difficulty' of time detected in the beforeGameScreens() operation.
    -------------------------------------------------------------------*/


    /****** new high score operation ******/
    bool newHighScore();
    /*-----------------------------------------------------------------
    checks if the player made a new high score or not

    Precondition: old score.
    Postcodition: returns true if the player made a new highscore and false if not.
    -------------------------------------------------------------------*/

    const int cellsize = 30;
    const int cellcount = 25;
    int offsetWidth = GetScreenWidth() - cellsize * cellcount;
    int offsetHeight = GetScreenHeight() - cellsize * cellcount;

    Sound eatSound;
    Sound welcomeSound;
    Sound newScoreSound;
    Sound gameOverSound;
    Sound selectSound;
    bool btnAction;
    Texture2D texture1;
    Vector2 mousePoint = { 0.0f, 0.0f };

private:

    /******** Data Members ********/
    bool allowmove;                     // to control inputs from the user
    double lastUpdatedTime;             // to save the last time snake was updated depending on difficulty
    bool modern;                        // to choose between modern and classic game
    int gScore = 0;                     // to store the current score of the game
    int hScore = 0;                     // to store the high score of the game 
    bool pause = 0;                     // To pause the game
    double difficulty;                  // to specify the game speed
    typedef enum GameScreen { LOGO = 0, TITLE, TYPE, GAMEPLAY, GAMEOVER } GameScreen;
    GameScreen currentScreen = LOGO;

    /******** Snake and Food objects initialization ********/
    Snake snake;
    Food food;

}; //------- end of the Game class
#endif
