#include "Snake.h"
#include <stdio.h>
#include <cassert>
#include "raylib.h"

using namespace std;


//--- Definition of the class constuctor
Snake::Snake() // scope operator used to define that Snake() is member function in class Snake
    : first(0), mySize(0)
{
    insert((offsetWidth/30)+2 , (offsetHeight/30) + 2, 0);
    Image image = LoadImage("Graphics/right-head.png");
    ImageResizeNN(&image, cellsize, cellsize);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}


//--- Definition of the class destructor
Snake::~Snake()
{
    Snake::NodePointer prev = first,
        ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
    UnloadTexture(texture);
}


//--- Definition of insert()
void Snake::insert(int posx,int posy, int index)
{
    if (index < 0 || index > mySize)
    {
        // cerr waits for you to see the error and take any action
        cerr << "*** Illegal location to insert -- " << index << " --in this Snake ***\n";
        return; // btseb el function w trg3 mkan ma 7sal calling
        // exit(1):terminates all the program and get out
    }
    mySize++;
    Snake::NodePointer newPtr = new Node(posx,posy),
        predPtr = first;
    if (index == 0)
    {
        newPtr->next = first;
        first = newPtr;
    }
    else
    {
        for (int i = 1; i < index; i++) // hanm4i pointer lhad elnode aly h3ml insert b3dha
        {
            predPtr = predPtr->next;
        }
        newPtr->next = predPtr->next;
        predPtr->next = newPtr;
    }
}


//--- Definition of Draw()
void Snake::Draw() {
    NodePointer ptr = first;
    while (ptr != 0) {
        int px = ptr->PosX;
        int py = ptr->PosY;
        int dir = 0;
        Rectangle segment = Rectangle{ float(px * cellsize),float(py * cellsize),30,30};
        if (ptr == first) {
            //---- if you want an image for the first node
            if (x == 0 && y == 1) {
                dir = 90;
                px++;
            }
            else if (x == 1 && y == 0) {
                dir = 0;
            }
            else if (x == 0 && y == -1) {
                dir = 270;
                py++;
            }
            else if (x == -1 && y == 0) {
                dir = 180;
                px++;
                py++;
            }
            DrawTextureEx(texture, {float(px * cellsize), float(py * cellsize)},dir,1, GREEN);
            //DrawRectangleRounded(segment, 0.7, 6, DARKBLUE);
        }else{ 
            //DrawRectangle(px * 30, py * 30, 30, 30, BLUE); 
            DrawRectangleRounded(segment,0.7, 6,DARKGREEN);
        }
        ptr = ptr->next;
    }
}


//--- Definition of update()
void Snake::update() {
    NodePointer ptr = first;
    if (mySize == 1) {
        ptr->PosX += x;
        ptr->PosY += y;
    }
    else {
        erase(mySize - 1);
        insert(ptr->PosX + x, ptr->PosY + y, 0);
    }
}


//--- Definition of erase()
void Snake::erase(int index)
{
    if (index < 0 || index >= mySize)
    {
        cerr << "Illegal location to delete -- " << index << ". Snake unchanged ***\n";
        return;
    }
    // decrease the Snake size
    mySize--;

    Snake::NodePointer ptr,
        predPtr = first;
    if (index == 0)
    {
        ptr = first;
        first = ptr->next;
        delete ptr;
    }
    else
    {
        for (int i = 1; i < index; i++)
        {
            predPtr = predPtr->next;
        }
        ptr = predPtr->next;
        predPtr->next = ptr->next;
        delete ptr;
    }
}


//--- Definition of boundCollision()
bool Snake::boundCollision(bool mod)
{
    if (!mod) {
        if (first->PosX == (offsetWidth/30)-1 || first->PosY == (GetScreenHeight() - offsetHeight) / 30 || first->PosY == (offsetHeight / 30) -1 || first->PosX == (GetScreenWidth() - offsetWidth) / 30)
        {
            return true;
        }
        return false;
    }
    else {
        if (first->PosX == (offsetWidth / 30) - 1)     // left collision
        {
            first->PosX = (GetScreenWidth()- offsetWidth)/30-1;
        }
        if (first->PosY == (GetScreenHeight() - offsetHeight) / 30) //down collision
        {
            first->PosY = offsetHeight / 30;
        }
        if (first->PosY == (offsetHeight / 30) - 1)    //up collision
        {
            first->PosY = (GetScreenHeight() - offsetHeight) / 30-1;
        }
        if (first->PosX == (GetScreenWidth()-offsetWidth) /30)  //right collision
        {
            first->PosX = offsetWidth / 30;
        }
        return false;
    }
}


//--- Definition of selfCollision()
bool Snake::selfCollision()
{
    NodePointer ptr = first->next;
    while (ptr != NULL)
    {
        if (first->PosX == ptr->PosX && first->PosY == ptr->PosY)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}


//--- Definition of reset()
void Snake::reset() {
    int siz = mySize;
    if (mySize > 1) {
        for (int i = 0; i < siz-1; i++) {
            erase(0);
        }
    }
    first->PosX = (offsetWidth / 30) + 2;
    first->PosY = (offsetHeight / 30) + 2;
    x = 1;
    y = 0;
    score = 0;
}


//--- Definition of IsSnakeBody()
bool Snake::IsSnakeBody(int x, int y) {
    NodePointer ptr = first;
    while (ptr != 0) {
        if (ptr->PosX == x && ptr->PosY == y) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}


//--- Definition of EatingCheck()
bool Snake::EatingCheck(int px, int py) {
    bool eaten = false;
    if (first->PosX ==px && first->PosY == py) {
        insert(first->PosX+x, first->PosY+y, 0);
        score++;
        eaten = true;
    }
    return eaten;
}

