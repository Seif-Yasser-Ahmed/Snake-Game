//
// Snake.h
// Snake Game using linked-list
//
// Created                  on 19/11/2023  "dd/mm/yyyy"
// Updated by Seif Yasser   on 21/11/2023
// Updated by Ali Tarek     on 23/11/2023 
// Updated by Seif Yasser   on 25/11/2023
// Updated by Gaser Zaghlol on 26/11/2023
// Updated by Arwa Faisal   on 27/11/2023
/*-------------------Snake.h------------------------

 This Header line defines the data type Snake for processing Snakes.

 Basic operations are:
 ---------------------------------------------------
 Constructor
 Destructor
 insert:			 Insert a node to snake
 erase:				 Remove a node from snake
 Draw:               Draws the snake on GUI
 update:             Updates the snake state every frame
 eventTriggered:     Trigger to control the game speed
 selfCollision:      Check collisions of snake with itself
 boundCollision:     Check collisions of snake with boundaries
 reset:              Resets the snake to the very initial state
 IsSnakeBody:        checks position of every node on snake
 EatingCheck:        checks if snake ate food
 newHighScore:       checks if the player made a new score

---------------------------------------------------*/

#include <iostream>
#include "raylib.h"
using namespace std;

#pragma once // makes the "Snake.h" to be loaded in the memory only one time


#ifndef SNAKE_H
#define SNAKE_H
class Snake
{
public:
    /************ Function Members *************/

    /********* Class Constructor **********/
    Snake();
    /*-----------------------------------------------------------------
    Construct a Snake object

    Precondition: None
    Postcodition: An empty Snake object has been constructed; mySize=0.
    -------------------------------------------------------------------*/

    
    /********* Class destructor **********/
    ~Snake();
    /*-----------------------------------------------------------------
    Destroys a Snake object

    Precondition: The life of a Snake object is over
    Postcodition: The memory dynamically allocated by the constructor for the array pointed to myArray has been returned to the heap.
    -------------------------------------------------------------------*/


    /****** insert Snake node operation ******/
    void insert(int posx, int poxy, int index);
    /*-----------------------------------------------------------------
    insert a posX and PosY into the Snake at a given position

    Precondition: index is a valid Snake index:0<=index<=mySize
    Postcodition: posX and posY has been inserted as data into the Snake Node at position index determined by index.
    -------------------------------------------------------------------*/


    /****** erase Snake node operation ******/
    void erase(int index);
    /*-----------------------------------------------------------------
    Remove a node from the Snake at a given index

    Precondition: The Snake is not empty;
                  The index satisfies 0<=index<mySize.;
    Postcodition: node at position index determined by index has been removed (provided pos is a legal position).
    -------------------------------------------------------------------*/


    /****** draw the snake operation ******/
    void Draw();
    /*-----------------------------------------------------------------
    draws the snake on the screen

    Precondition: size of the snake to loop on;
    Postcodition: draws the snake on the GUI screen.
    -------------------------------------------------------------------*/


    /****** update the snake position operation ******/
    void update();
    /*-----------------------------------------------------------------
    update the snake position every frame (60 times per second) in the main loop.

    Precondition: None.
    Postcodition: update every node's position in the snake within the time detected by the eventtriggered function.
    -------------------------------------------------------------------*/


    /****** eventTriggered to control the speed of the snake based on time operation ******/
    bool eventTriggered(double interval);
    /*-----------------------------------------------------------------
    check if a specific time has passed like the CLK in the CPU to update the snake position in the GUI

    Precondition: interval of time to trigger after.
    Postcodition:returns true or false based on if the interval specified passed or not.
    -------------------------------------------------------------------*/


    /****** self collision check operation ******/
    bool selfCollision();
    /*-----------------------------------------------------------------
    checks self collitions of the snake and it's tail

    Precondition: posX and posY of all snake nodes.
    Postcodition: returns true if the collision happend and false if not.
    -------------------------------------------------------------------*/


    /****** boundaries collision check operation ******/
    bool boundCollision(bool mod);
    /*-----------------------------------------------------------------
    checks boundaries collitions of the snake and walls

    Precondition: posX and posY of snake head and the walls
    Postcodition: if(classic)returns true if the collision happend and false if not, if(modern) returns false all the time and make the snake get out the other side.
    -------------------------------------------------------------------*/


    /****** reset the snake operation ******/
    void reset();
    /*-----------------------------------------------------------------
    reset the snake to the initial state to play again the game

    Precondition: number of nodes of the snake to loop on and remove all extra nodes
    Postcodition: the snake is reseted to the initial state and ready to start the game again.
    -------------------------------------------------------------------*/


    /****** is on snake operation ******/
    bool IsSnakeBody(int x, int y);
    /*-----------------------------------------------------------------
    checks if a position (x,y) is on the snake on any node

    Precondition: position *x,y) of element to check on & position of every node of the snake,
    Postcodition: returns true if the element is on the same position as a snake node.
    -------------------------------------------------------------------*/


    /****** check eating operation ******/
    bool EatingCheck(int px,int py);
    /*-----------------------------------------------------------------
    checks if the snake ate food or not

    Precondition: position of food (x,y) and posiiton of the snake head (x,y) to check on.
    Postcodition: returns true if the snake head has eaten a food.
    -------------------------------------------------------------------*/


    /****** high score operation ******/
    bool newHighScore();
    /*-----------------------------------------------------------------
    checks if the player made a new high score or not

    Precondition: old score.
    Postcodition: returns true if the player made a new highscore and false if not.
    -------------------------------------------------------------------*/


    /****** x and y for the next direction of the snake nodes ******/
    int x = 1, y = 0;
    int score = 0;
    int highScore = 0;

private:
    

    /******** Class Node for the linked-Snake ********/
    class Node
    {
    public:
        //------- Node data members
        Node* next;
        int PosX;
        int PosY;
        //------- Node operations
        //------- Default constructor
        Node() : next(0) {} // initialize next to zero

        //------- Explicit-value constructor
        Node(int posx, int posy) :PosX(posx), PosY(posy), next(0) {}
        // initialize dat to dataValue and next to zero
    };
    //------- End of Node class

    typedef Node* NodePointer;

    /******** Data Members ********/
    int mySize; // current size of the snake=score+1
    NodePointer first;
    Texture2D texture;
    double lastUpdatedTime;

}; //------- end of the List class
#endif
