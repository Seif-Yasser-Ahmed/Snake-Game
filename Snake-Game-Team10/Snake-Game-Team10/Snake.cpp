#include "Snake.h"
#include <stdio.h>
#include <cassert>
#include "raylib.h"
using namespace std;

//--- Definition of the class constuctor
Snake::Snake() // scope operator used to define that Snake() is member function in class Snake
    : first(0), mySize(0)
{
    insert(6, 8, 0);
    insert(5, 8, 0);
    insert(4, 8, 0);
    Image image = LoadImage("Graphics/head.png");
    ImageResizeNN(&image, 30, 30);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

//--- Definition of the copy constructor
Snake::Snake(const Snake& origSnake)
    : first(0), mySize(origSnake.mySize)
{
    if (mySize == 0)
        return;
    Snake::NodePointer origPtr, lastPtr;
    first = new Node(origSnake.first->data);
    lastPtr = first;
    origPtr = origSnake.first->next;
    while (origPtr != 0) // till origPtr points to last next in last node that it is NULL
    {
        lastPtr->next = new Node(origPtr->data);
        origPtr = origPtr->next; // it's like origPtr++
        lastPtr = lastPtr->next; // it's like lastPtr++
    }
}

//--- Definition of the class destructor
inline Snake::~Snake()
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

//--- Definition of size()
int Snake::size() {
    int size = 1;
    NodePointer ptr = first;
    while (ptr->next != 0) {
        ptr = ptr->next;
        size++;
    }
    return size;
}


//--- Definition of empty()
bool Snake::empty() const
{
    return mySize == 0;
}

//--- Deifinition of the assignment operator
const Snake& Snake::operator=(const Snake& rightSide)
{
    mySize = rightSide.mySize;
    first = 0;
    if (mySize == 0)
        return *this;
    if (this != &rightSide)
    {
        this->~Snake();
        Snake::NodePointer origPtr, lastPtr;
        first = new Node(rightSide.first->data);
        lastPtr = first;
        origPtr = rightSide.first->next;
        while (origPtr != 0) // till origPtr points to last next in last node that it is NULL
        {
            lastPtr->next = new Node(origPtr->data);
            origPtr = origPtr->next; // it's like origPtr++
            lastPtr = lastPtr->next; // it's like lastPtr++
        }
    }
    return *this;
}

//--- Definition of display()
void Snake::display(ostream& out) const // insted of "cout" to output on any output stream or output operator whatever what it is using ostream
{
    Snake::NodePointer Ptr = first;
    while (Ptr != 0)
    {
        out << Ptr->data << "	";
        Ptr = Ptr->next;
    }
}
/*------------------------------------------------------------------------------------------------------------------ */
/*overloading the << operator that it displays the Snake immediatlely once it sees Snake after the << operator
hytl3 3al ostream whatever its cout or what*/
/*------------------------------------------------------------------------------------------------------------------ */

//--- Definition of output operator
ostream& operator<<(ostream& out, const Snake& aSnake)

{
    aSnake.display(out); // display on out operator
    return out;
}

//--- Definition of the input operator
istream& operator>>(istream& in, Snake& aSnake)
{
    ElementType val;
    in >> val;
    aSnake.insert(val, aSnake.mySize); // Needed friend in header file to access mySize
    return in;
}

//--- Definition of insert()
void Snake::insert(ElementType dataVal, int index)
{
    if (index < 0 || index > mySize)
    {
        // cerr waits for you to see the error and take any action
        cerr << "*** Illegal location to insert -- " << index << " --in this Snake ***\n";
        return; // btseb el function w trg3 mkan ma 7sal calling
        // exit(1):terminates all the program and get out
    }
    mySize++;
    Snake::NodePointer newPtr = new Node(dataVal),
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

Snake::Snake(int siz) : first(0), mySize(0) {
    

}

void Snake::Draw() {
    NodePointer ptr = first;
    while (ptr != 0) {
        int x = ptr->PosX;
        int y = ptr->PosY;
        DrawTexture(texture, x * 30, y * 30, WHITE);
        //DrawRectangle(x * 30, y * 30, 30, 30, DARKGREEN);
        ptr = ptr->next;
    }
}

void Snake::update() {
    /*first->next->PosX = first->PosX;
    first->next->PosY = first->PosY;
    first->PosX = first->PosX + x;
    first->PosY = first->PosY + y;*/
    NodePointer ptr = first;
    erase(0);
    insert(ptr->PosX + x, ptr->PosY + y, mySize);
    
    //append(first->PosX +x, first->PosY+y);
}

bool Snake::eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdatedTime >= interval) {
        lastUpdatedTime = currentTime;
        return true;
    }
    return false;
}

void Snake::append(int x,int y)
{
    NodePointer temp = first;
    while (temp->next != 0)
    {
        temp = temp->next;
    }
    NodePointer newnode = new Node();
    newnode->PosX = x;
    newnode->PosY = y;

    temp->next = newnode;
    newnode->next = 0;
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

/*
//--- Definition of deleteByValue()
void Snake::deleteByValue(ElementType item) {
    Snake::NodePointer Ptr = first;
    int index = 0;
    while (Ptr->next != 0) {
        if (Ptr->data == item)
            erase(index);
        Ptr = Ptr->next;
        index++;
    }
}

//--- Definition of reverse()
void Snake::reverse() {
    Snake::NodePointer currentPtr = first, nextPtr, prevPtr = 0;
    while (currentPtr != 0) {
        nextPtr = currentPtr->next; //make nextPtr points at the next node
        currentPtr->next = prevPtr; //make the next pointer in the current node points at previous node to reverse it
        prevPtr = currentPtr;		//make the prevPtr points at the current node to remake the loop
        currentPtr = nextPtr;		//make the nextPtr points at the next node
    }
    Snake::first = prevPtr;
    /****************** another way to do it ******************

    for (; currentPtr1 != 0; prevPtr1 = currentPtr1, currentPtr1 = nextPtr1) {
        nextPtr1 = currentPtr1->next;
        currentPtr1->next = prevPtr1;
    }
    Snake::first = prevPtr1;
}


//--- Definition of ascendingOrder()
bool Snake::ascendingOrder() {
    NodePointer prevPtr = first, tempPtr = first->next;
    if (mySize <= 1) {
        cout << "********** the Snake has only one element **********" << endl;
        return true;
    }
    while (prevPtr->next != 0) {
        if (prevPtr->data > tempPtr->data) {
            return false;
        }
        prevPtr = prevPtr->next;
        tempPtr = tempPtr->next;
    }
    return true;
}
*/
