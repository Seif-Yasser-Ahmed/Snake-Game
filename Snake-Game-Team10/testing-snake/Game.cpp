#include "Game.h"
#include <stdio.h>
#include <cassert>
#include "raylib.h"

using namespace std;


//--- Definition of the class constructor
Game::Game() {
    InitAudioDevice();
    eatSound = LoadSound("Sounds/Eat2.mp3");
    welcomeSound = LoadSound("Sounds/welcome1.mp3");
    newScoreSound = LoadSound("Sounds/newScore.mp3");
    gameOverSound = LoadSound("Sounds/gameOver2.mp3");
    selectSound = LoadSound("Sounds/Select.mp3"); 
    Image image = LoadImage("Graphics/Play.png");
    ImageResizeNN(&image, cellsize*4, cellsize);
    texture1 = LoadTextureFromImage(image);
    UnloadImage(image);
}


//--- Definition of the class destructor
Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(welcomeSound);
    UnloadSound(newScoreSound);
    UnloadSound(gameOverSound);
    UnloadSound(selectSound);
    CloseAudioDevice();
    UnloadTexture(texture1);
}


//--- Definition of Draw()
void Game::Draw() {
	snake.Draw();
	food.Draw();
}


//--- Definition of update()
void Game::update() {
    // ********************** right arrow **********************
    if (IsKeyPressed(KEY_RIGHT) && snake.x != -1 && allowmove) {
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
	if (eventTriggered(difficulty)) {
		snake.update();
        allowmove = true;
	}
}


//--- Definition of eventTriggered()
bool Game::eventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdatedTime >= interval) {
		lastUpdatedTime = currentTime;
		return true;
	}
	return false;
}



//--- Definition of duringGameScreen()
void Game::duringGameScreen() {
    switch (currentScreen){
    case LOGO:
        {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)|| IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )
        {
            PlaySound(selectSound);
            currentScreen = TYPE;
        }
        DrawText("WELCOME TO OUR GAME", GetScreenWidth() / 2 - 250, 80, 50, BLACK);
        DrawText("Spicy", GetScreenWidth() / 2 - 250, 150, 60, RED);
        DrawText("Snake Game", GetScreenWidth() / 2-70, 155, 60, BLACK);
        DrawText("TEAM 10!", GetScreenWidth() / 2 - 250, 320, 40, BLACK);
        DrawText("Seif Yasser", GetScreenWidth() / 2 - 250, 390, 40, BLACK);
        DrawText("Ali Tarek", GetScreenWidth() / 2 - 250, 440, 40, BLACK);
        DrawText("Gaser Zaghlol", GetScreenWidth() / 2 - 250, 490, 40, BLACK);
        DrawText("Arwa faisal", GetScreenWidth() / 2 - 250, 540, 40, BLACK);
        DrawText("21P0102", GetScreenWidth() / 2+50, 390, 40, BLACK);
        DrawText("21P0123", GetScreenWidth() / 2+50, 440, 40, BLACK);
        DrawText("21P0052", GetScreenWidth() / 2+50, 490, 40, BLACK);
        DrawText("21P0073", GetScreenWidth() / 2+50, 540, 40, BLACK);
        DrawText("Press Enter or Space to play", GetScreenWidth() / 2 - 250, 650, 40, BLACK);
    }break;
    case TYPE:
    {
        // modern or classic
        if (IsKeyPressed('1')) {
            modern = true;
            currentScreen = TITLE;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('2')) {
            modern = false;
            currentScreen = TITLE;
            PlaySound(selectSound);

        }
        DrawText("Which one do you want to play?", GetScreenWidth() / 2 - 350, 300, 45, BLACK);
        DrawText("1.Modern      2.Classic", GetScreenWidth() / 2 - 150, 420, 30, BLACK);
    }break;
    case TITLE:
    {
        // setting the difficulty
        if (IsKeyPressed('1'))
        {
            difficulty = 0.3;
            currentScreen = GAMEPLAY;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('2')) {
            difficulty = 0.2;
            currentScreen = GAMEPLAY;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('3')) {
            difficulty = 0.1;
            currentScreen = GAMEPLAY;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('4')) {
            difficulty = 0.05;
            currentScreen = GAMEPLAY;
            PlaySound(selectSound);

        }
        DrawText("Spicy Snake Game", GetScreenWidth() / 2 - 250, 20, 60, BLACK);
        DrawText("Select which difficulty you want", GetScreenWidth() / 2 - 300, 300, 40, BLACK);
        DrawText("1.Easy    2.Medium    3.Hard  4.Impossible", GetScreenWidth() / 2 - 200, 400, 20, BLACK);

    } break;
    case GAMEPLAY:
    {
        DrawRectangleLinesEx(Rectangle{ (float)offsetWidth - 5,(float)offsetHeight - 5,(float)GetScreenWidth() - 2 * offsetWidth + 10,(float)GetScreenHeight() - 2 * offsetHeight + 7 }, 5, DARKGREEN);
        if (IsKeyPressed(KEY_SPACE)) pause = !pause; // pausing the game
        if (!pause)
        {
            update();
            // ********************** self & bound collisions **********************
            if (snake.selfCollision() || snake.boundCollision(modern)) {
                currentScreen = GAMEOVER;
                gScore = snake.score;
                if (newHighScore()) {
                    hScore = gScore;
                }
                snake.reset();
                break;
            }
            // ********************** eating food **********************
            if (snake.EatingCheck(food.PosX, food.PosY)) {
                PlaySound(eatSound);
                if (snake.score == (cellsize*cellcount)-1) {                                  // checks if snake size == area of the screen to game over the game
                    currentScreen = GAMEOVER; 
                }
                food.GetRandomPosition();
                if (snake.IsSnakeBody(food.PosX, food.PosY)) {
                    food.GetRandomPosition();
                }
            }
            // ********************** home screen **********************
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = TYPE;
            }
        }
        else if (pause) DrawText("paused", GetScreenWidth() / 2-60, GetScreenHeight()/2-50, 30, BLACK);             // when pausing the game

        DrawText(TextFormat("%i", snake.score), 80, 80, 30, BLACK);        // draw score on screen
        Draw();                                                             // drawing the snake

    } break;
    case GAMEOVER:
    {
        if (IsKeyPressed('1'))
        {
            currentScreen = GAMEPLAY;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('2')) {
            currentScreen = TITLE;
            PlaySound(selectSound);

        }
        else if (IsKeyPressed('3')) {
            currentScreen = TYPE;
            PlaySound(selectSound);

        }
        DrawText("GAME OVER!", GetScreenWidth() / 2 - 250, 330, 60, BLACK);
        DrawText("Score: ", GetScreenWidth() / 2 - 250, 430, 45, BLACK);
        DrawText(TextFormat("%i", gScore), GetScreenWidth() / 2+50, 430, 45, BLACK);
        DrawText("High Score: ", GetScreenWidth() / 2 - 250, 480, 45, BLACK);
        DrawText(TextFormat("%i", hScore), GetScreenWidth() / 2+50, 480, 45, BLACK);
        DrawText("1.Play again  2.Choose other difficulty   3.change game mood", GetScreenWidth() / 2 - 400, 560, 28, BLACK);
    }
    default:break;
    }
}


//--- Definition of newHighScore
bool Game::newHighScore() {
    if (gScore >= hScore) {
        hScore = gScore;
        return true;
    }
    return false;
}