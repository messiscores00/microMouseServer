//This is an edit to my code.
#include "micromouseserver.h"
#include <iostream>
#include <string>
using namespace std;
#define ARRAY_LENGTH 20
#define LEFT 0
#define RIGHT 2
#define FORWARD 1
#define BACK 3


/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/


//global variables
int array1 [ARRAY_LENGTH][ARRAY_LENGTH];//a 20 by 20 array
int x = 0;//x position of the mouse
int y = 0;//y position of the mouse
bool Setarray = false;//to test to see if you have set all of the array to -1
bool mouseto1 = false;//to see if you have set the bottom left corner to 1
int orientation = FORWARD;//0=face left / 1=face forwards / 2=face right / 3=face back


//these frunctions are used to help write less code
int Infront (int newPos){
    int Pos;
    if(orientation == FORWARD){
        if(newPos == -1)
            Pos = array1[::x][::y+1];
        else
            Pos = array1[::x][::y+1] = newPos;
    }
    if(orientation == LEFT){
        if(newPos == -1)
            Pos = array1[::x-1][::y];
        else
            Pos = array1[::x-1][::y] = newPos;
    }
    if(orientation == RIGHT){
        if(newPos == -1)
            Pos = array1[::x+1][::y];
        else
            Pos = array1[::x+1][::y] = newPos;
    }
    if(orientation == BACK){
        if(newPos == -1)
            Pos = array1[::x][::y-1];
        else
            Pos = array1[::x][::y-1] = newPos;
    }
    return Pos;
}


int Right(int newPos){
    int Pos;
    if(orientation == FORWARD){
        if(newPos == -1)
            Pos = array1[::x+1][::y];
        else
            Pos = array1[::x+1][::y] = newPos;
    }
    if(orientation == LEFT){
        if(newPos == -1)
            Pos = array1[::x][::y+1];
        else
            Pos = array1[::x][::y+1] = newPos;
    }
    if(orientation == RIGHT){
        if(newPos == -1)
            Pos = array1[::x][::y-1];
        else
            Pos = array1[::x][::y-1] = newPos;
    }
    if(orientation == BACK){
        if(newPos == -1)
            Pos = array1[::x-1][::y];
        else
            Pos = array1[::x-1][::y] = newPos;
    }
    return Pos;
}


int Left(int newPos){
    int Pos;
    if(orientation == FORWARD){
        if(newPos == -1)
            Pos = array1[::x-1][::y];
        else
            Pos = array1[::x-1][::y] = newPos;
    }
    if(orientation == LEFT){
        if(newPos == -1)
            Pos = array1[::x][::y-1];
        else
            Pos = array1[::x][::y-1] = newPos;
    }
    if(orientation == RIGHT){
        if(newPos == -1)
            Pos = array1[::x][::y+1];
        else
            Pos = array1[::x][::y+1] = newPos;
    }
    if(orientation == BACK){
        if(newPos == -1)
            Pos = array1[::x+1][::y];
        else
            Pos = array1[::x+1][::y] = newPos;
    }
    return Pos;
}


int Back(int newPos){
    int Pos;
    if(orientation == FORWARD){
        if(newPos == -1)
            Pos = array1[::x][::y-1];
        else
            Pos = array1[::x][::y-1] = newPos;
    }
    if(orientation == LEFT){
        if(newPos == -1)
            Pos = array1[::x+1][::y];
        else
            Pos = array1[::x+1][::y] = newPos;
    }
    if(orientation == RIGHT){
        if(newPos == -1)
            Pos = array1[::x-1][::y];
        else
            Pos = array1[::x-1][::y] = newPos;
    }
    if(orientation == BACK){
        if(newPos == -1)
            Pos = array1[::x][::y+1];
        else
            Pos = array1[::x][::y+1] = newPos;
    }
    return Pos;
}


void microMouseServer::studentAI() {

    //set all elements to the array to -1(once)
    if(::Setarray==false){//if the array is already set do nothing
        for(int i = 0; i < ARRAY_LENGTH; i += 1){
            for(int a = 0; a < ARRAY_LENGTH; a += 1){
                array1[i][a]=-1;
            }
        }
        ::Setarray = true;
    }


    //make mouse to 1(once)
    if(mouseto1 ==false){
        array1[::x][::y] = 1;
        mouseto1 = true;
    }


    //make everything around the mouse to 0 if it is -1 and if space is there
    //infront
    if(!isWallForward()){
        if(Infront(-1)==-1){
            Infront(0);
        }
    }
    //Right
    if(!isWallRight()){
        if(Right(-1)==-1){
            Right(0);
        }
    }
    //Left
    if(!isWallLeft()){
        if(Left(-1)==-1){
            Left(0);
        }
    }

printUI(std::to_string(Infront(-1)).c_str());
//printUI(std::to_string(Right(-1)).c_str());
//printUI(std::to_string(Left(-1)).c_str());

    //Left Hand rule+right
    if(!isWallLeft()&&((Left(-1)<=Infront(-1)||Left(-1)==0)||(Left(-1)<=Right(-1)||Left(-1)==0))){//if space is left
        turnLeft();
        moveForward();

        if(::orientation == FORWARD){
            ::x = ::x - 1;
            ::orientation = LEFT;
        }
        else if(::orientation == RIGHT){
            ::y = ::y +1;
            ::orientation = FORWARD;
        }
        else if(::orientation == BACK){
            ::x = ::x +1;
            ::orientation = RIGHT;
        }
        else if(::orientation == LEFT){
            ::y = ::y - 1;
            ::orientation = BACK;
        }
    }


    else if (!isWallForward()&&((Infront(-1)<=Right(-1))||(Infront(-1)==0))){//if there is a space infront
        moveForward();

        if(::orientation == FORWARD){
            ::y = ::y + 1;
        }
        else  if(::orientation == RIGHT){
            ::x = ::x + 1;
        }
        else  if(::orientation == BACK){
            ::y = ::y - 1;
        }
        else    if(::orientation == LEFT){
            ::x = ::x - 1;
        }
    }


    else if(!isWallRight()){//if there is a space to the right
        turnRight();
        moveForward();

        if(::orientation == FORWARD){
            ::x  = ::x + 1;
            ::orientation = RIGHT;
        }
        else  if(::orientation == RIGHT){
            ::y = ::y - 1;
            ::orientation = BACK;
        }
        else if(::orientation == BACK){
            ::x = ::x - 1;
            ::orientation = LEFT;
        }
        else  if(::orientation == LEFT){
            ::y = ::y + 1;
            ::orientation = FORWARD;
        }
    }


    else if(isWallRight()){//if there is a wall to the left & infront & to the right
        //180 turn
        turnRight();
        turnRight();
        moveForward();

        if(::orientation == FORWARD){
            ::y = ::y - 1;
            ::orientation = BACK;
        }
        else  if(::orientation == RIGHT){
            ::x = ::x - 1;
            ::orientation = LEFT;
        }
        else if(::orientation == BACK){
            ::y = ::y + 1;
            ::orientation = FORWARD;
        }
        else  if(::orientation == LEFT){
            ::x = ::x + 1;
            ::orientation = RIGHT;
        }
    }


    //set the mouse to the position behind it. When the position behind the mouse is equal to the position the mouse is in set the position of the mouse to behind it plus one.
    if(!(array1[::x][::y] == Back(-1))){
        array1[::x][::y] = Back(-1);
    }
    else {
        array1[::x][::y] = Back(-1) + 1;
    }


    //Find the end of the maze.
}
//printUI(std::to_string().c_str());
