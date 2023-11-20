//
// Snake.h
// Snake Game using linked-list
//
// Created by Seif Yasser on 19/11/2023  "dd/mm/yyyy"
//
/*-------------------Snake.h------------------------

 This Header line defines the data type Snake for processing Snakes.
 Basic operations are:
 Constructor
 empty:				 Check if Snake is empty
 insert:			 Insert a node to snake
 erase:				 Remove an item
 display:			 Output the Snake
 <<:				 Output operator

 *-----------Extra operations-------------------*

 deleteByValue:		 Remove item by value
 leftRotation:		 Rotate the Snake to the left
 removeDuplicates:	 Remove Duplicated values
---------------------------------------------------*/

#include <iostream>
#include "raylib.h"
using namespace std;

#pragma once // makes the "Snake.h" to be loaded in the memory only one time

typedef int ElementType;

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

    /********* Copy Constructor **********/
    Snake(const Snake& origSnake);
    /*-----------------------------------------------------------------
    Copy constructor

    Precondition: a copy of origSnake is needed
    Postcodition:A copy of origSnake has been constructed.
    -------------------------------------------------------------------*/

    /********* Class destructor **********/
    ~Snake();
    /*-----------------------------------------------------------------
    Destroys a Snake object

    Precondition: The life of a Snake object is over
    Postcodition: The memory dynamically allocated by the constructor for the array pointed to myArray has been returned to the heap.
    -------------------------------------------------------------------*/

    /********* Assignment operator **********/
    const Snake& operator=(const Snake& rightHandSide);
    /*-----------------------------------------------------------------
    Assign a copy of a Snake object to the current object.

    Precondition: None.
    Postcodition: A copy of rightHandSide has been assigned to this object, A const reference to this Snake is returned.
    -------------------------------------------------------------------*/

    /****** empty operation ******/
    bool empty() const; // const: means that this function can not change member variables of the class
    /*-----------------------------------------------------------------
    Check if a Snake is empty

    Precondition: None
    Postcodition: True is returned if the Snake is empty, False if not.
    -------------------------------------------------------------------*/

    /****** insert and erase operations ******/
    void insert(ElementType dataVal, int index);
    /*-----------------------------------------------------------------
    insert a value into the Snake at a given position

    Precondition: index is a valid Snake index:0<=index<=mySize
    Postcodition: dataVal has been inserted into the Snake at position index determined by pos (provided there is room and pos is a legal position).
    -------------------------------------------------------------------*/

    void erase(int index);
    /*-----------------------------------------------------------------
    Remove a value into the Snake at a given index

    Precondition: The Snake is not empty;
                  The index satisfies 0<=index<mySize.;
    Postcodition: element at position index determined by index has been removed (provided pos is a legal position).
    -------------------------------------------------------------------*/

    /****** search operation ******/
    int search(ElementType dataVal);
    /*-----------------------------------------------------------------
    Search for data value in this Snake

    Precondition: None;
    Postcodition: Index of node containing dataVal will be returned,
    if such a node is found, -1r if not.
    -------------------------------------------------------------------*/

    /****** output operation ******/
    void display(ostream& out) const;
    /*-----------------------------------------------------------------
    Display a Snake

    Precondition: The pstream out is open;
    Postcodition: the Snake represented by this Snake object has been inserted into out to be desplayed.
    -------------------------------------------------------------------*/

    /****** delete by value operation ******/
    void deleteByValue(ElementType item);
    /*-----------------------------------------------------------------
    Delete element by value in a Snake

    Precondition: the item to be deleted;
    Postcodition: element determined has been deleted.
    -------------------------------------------------------------------*/

    /****** delete by value operation ******/
    void leftRotation(int numOfRotations);
    /*-----------------------------------------------------------------
    each element of the array will be shifted to its left by one position
    and the first element of the array will be added to end of the Snake

    Precondition: number of rotations to be made.
    Postcodition: the Snake represented will be left rotated.
    -------------------------------------------------------------------*/

    /****** delete by value operation ******/
    void removeDuplicates();
    /*-----------------------------------------------------------------
    Removes duplicated items in a Snake

    Precondition: None
    Postcodition: the Snake will be updated as the duplicated items will be deleted.
    -------------------------------------------------------------------*/

    /****** reversing the Snake operation ******/
    void reverse();
    /*-----------------------------------------------------------------
    Reverse the Snake.

    Precondition: None
    Postcodition: the Snake will be reversed.
    -------------------------------------------------------------------*/

    /****** ascending checking operation ******/
    bool ascendingOrder();
    /*-----------------------------------------------------------------
    Check if the elements of this Snake are in ascending order.

    Precondition: None
    Postcodition: returns true if the linked Snake's elements are in ascending order and false if not.
    -------------------------------------------------------------------*/

    /********* Assignment operator **********/
    friend istream& operator>>(istream& in, Snake& aSnake);
    /*-----------------------------------------------------------------
    Insert an input of the user to the last node of the linked Snake

    Precondition: None.
    Postcodition: A new node in the end of the linked Snake will be added with data entered by the user during the runtime.
    -------------------------------------------------------------------*/

    /****** get size operation ******/
    int size();
    /*-----------------------------------------------------------------
    Returns the size of the linked list

    Precondition: None;
    Postcodition: size of the snake will be returned.
    -------------------------------------------------------------------*/

    /****** draw the snake operation ******/
    void Draw();
    /*-----------------------------------------------------------------
    draws the snake on the screen

    Precondition: size of the snake to loop on;
    Postcodition: draws the snake on the GUI screen.
    -------------------------------------------------------------------*/


    /****** insert and erase operations ******/
    void insert(int posx, int poxy,int index);
    /*-----------------------------------------------------------------
    insert a value into the Snake at a given position

    Precondition: index is a valid Snake index:0<=index<=mySize
    Postcodition: dataVal has been inserted into the Snake at position index determined by pos (provided there is room and pos is a legal position).
    -------------------------------------------------------------------*/

    /********* Class Constructor **********/
    Snake(int siz);
    /*-----------------------------------------------------------------
    Construct a Snake object

    Precondition: None
    Postcodition: An empty Snake object has been constructed; mySize=0.
    -------------------------------------------------------------------*/

    void update();

    bool eventTriggered(double interval);

    void append(int x, int y);
    
    
private:
    

    /******** Class Node for the linked-Snake ********/
    class Node
    {
    public:
        //------- Node data members
        ElementType data;
        Node* next;
        int PosX;
        int PosY;

        //------- Node operations
        //------- Default constructor
        Node() : next(0) {} // initialize next to zero

        //------- Explicit-value constructor
        Node(ElementType dataValue) : data(dataValue), next(0) {}
        Node(int posx,int posy):PosX(posx),PosY(posy),next(0) {}
        // initialize dat to dataValue and next to zero
    };
    //------- End of Node class

    typedef Node* NodePointer;

    /******** Data Members ********/
    
    Texture2D texture;
    double lastUpdatedTime;
public:
    int mySize; // current size of the list
    NodePointer first;
    int x=1, y=0;
}; //------- end of the List class
#endif

//---------- Prototype of output operator
ostream& operator<<(ostream& out, const Snake& asnake); // operator << overloading

/*****************************************
    overloading the << operator that when the compiler sees the << operator forget about the cout and come here to my overloaded operator
*****************************************/
