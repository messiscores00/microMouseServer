//This is an edit to my code.
#include "micromouseserver.h"
#include <iostream>
#include <string>
using namespace std;
#define array_length 20
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
int array1 [array_length][array_length];//a 20 by 20 array
int x = 0;//x position of the mouse
int y = 0;//y position of the mouse
bool Setarray = false;//to test to see if you have set all of the array to -1
bool arrayset1 = false;//to see if you have set the bottom left corner to 1
int orientation = 1;//0=face left / 1=face forwards / 2=face right / 3=face back
int var = 0;//for "for loops"
int var1 = 0;


void microMouseServer::studentAI() {
    if(::Setarray==false){//if the array is already set do nothing
        //set array to all -1s
        for(int i = 0; i < array_length; i += 1){
            for(int a = 0; a < array_length; a += 1){
                array1 [i][a]=-1;
            }
        }
        ::Setarray = true;
    }

    if(::arrayset1 ==false){
        array1[::x][::y] = 1;
        ::arrayset1 = true;
    }
    //set 0s around 1
    //come back /change "is walls" to something that doesn't kape
    /* if(!((::x == 0 || ::x == 19) && (::y == 0 || ::y == 19))){//if x-1 is 0-1 the array would be [-1][y] which can't happen
            if(array1[::x-1][::y] ==1 || array1[::x+1][::y]==1){//testing if any blocks around the array are 1 then it won't set anything to 0.
                if(!(array1[::x-1][::y] == 1)  ){//if to the left of the mouse is not 1(so -1 or 0)
                    if(!isWallLeft()){//if there is a space left
                        array1 [::x-1][::y] = 0;//setting the block to the left of the mouse to 0
                    }
                    if(!(array1[::x][::y+1] == 1) ){//if forwards is not 1(so 0 or 0)
                        if(!isWallForward()){//if there is a speace forwards(note that this is not infront of the mouse because infront of the mouse could be to the right or left)
                            array1 [::x][::y+1] = 0;//setting the block to forwards of the mouse to 0
                        }
                    }
                    if(!(array1[::x+1][::y] == 1)){//if to the right of the mouse is not 1(so 0 and -1)
                        if(!isWallRight()){//if there is a space to the right
                            array1 [::x+1][::y] = 0;//setting the block to the right of the mouse to 0
                        }
                    }
                }
            }
        }

*/

    //if mouse has already been there turn right
    bool A = true;
    while(A == true) {

        bool C = true;
        while(C == true){

            int z = array1[::x][::y];

            if(array1[::x][::y]==1||array1[::x][::y] < 1){
                array1[::x][::y] = array1[::x][::y] + 1;
            } else{
                array1[::x][::y] = 1;
            }

            C = false;

//check when x and y are being set cause this should work. also check orientation
            for(int i = 1; i < z + 1 ; i++){
//change put ::orientation
              // printUI(std::to_string(i).c_str());

                if( ((array1[::x][::y+1]==i)&&(::orientation == 1)) || ((array1[::x+1][::y]==i)&&(::orientation==2)) || ((array1[::x][::y-1]==i)&&(::orientation==3)) || ((array1[::x-1][::y]==i)&&(::orientation==0))) {//if the block infront of the mouse is 1(note that forwards is whatever the block ontop of the mouse and doesn't include its orientation)
                    if((array1[::x+1][::y]==z-i&&::orientation==1) || (array1[::x][::y-1]==z-i&&::orientation==2) || (array1[::x-1][::y]==z-i&&::orientation==3) || (array1[::x][::y+1]==z-i&&::orientation==0) ){//if the block to the right of the mouse is not 1(this includes the orientation so if the orientation moves the block to the right of the mouse will also move)


                        if(!isWallRight() ) {//if there is a blank space to the right

                            turnRight();
                            moveForward();

                            if(::orientation == 1){
                                ::x  = ::x + 1;
                                ::orientation = 2;

                            }

                            if(::orientation == 2){
                                ::y = ::y -1;
                                ::orientation = 3;
                            }

                            if(::orientation == 3){
                                ::x = ::x - 1;
                                ::orientation = 0;

                            }

                            if(::orientation == 0){
                                ::y = ::y + 1;
                                ::orientation = 1;
                            }
                            A = false;
                            C = false;
                        }
                    }
                }
            }
        }


        //Left Hand rule
        bool B= true;
        while(B==true){
            if(!isWallLeft()){//if space is left
                turnLeft();
                moveForward();

                if(::orientation == 1){
                    ::x = ::x - 1;
                    ::orientation = 0;

                }
                if(::orientation == 2){
                    ::y = ::y +1;
                    ::orientation = 1;
                }

                if(::orientation == 3){
                    ::x = ::x +1;
                    ::orientation = 2;

                }
                if(::orientation == 0){
                    ::y = ::y - 1;
                    ::orientation = 3;
                }

                A = false;
                B = false;
            }
            else if (!isWallForward()){//if there is a space infront
                moveForward();


                    if(::orientation == 1){
                        ::y = ::y + 1;
                        ::orientation = 1;
                    }

                    if(::orientation == 2){
                        ::x = ::x +1;
                        ::orientation = 2;

                    }
                    if(::orientation == 3){
                        ::y = ::y - 1;
                        ::orientation = 3;
                    }

                    if(::orientation == 0){
                        ::x = ::x -1;
                        ::orientation = 0;
                    }
                    A = false;
                    B = false;

            }
            else if(!isWallRight()){//if there is a space to the right

                turnRight();
                moveForward();

                if(::orientation == 1){
                    ::x  = ::x + 1;
                    ::orientation = 2;
                }

                if(::orientation == 2){
                    ::y = ::y - 1;
                    ::orientation = 3;
                }

                if(::orientation == 3){
                    ::x = ::x - 1;
                    ::orientation = 0;
                }

                if(::orientation == 0){
                    ::y = ::y + 1;
                    ::orientation = 1;
                }

                A = false;
                B = false;
            }
            else if(isWallRight()){//if there is a wall to the left & infront & to the right
                //180 turn
                turnRight();
                turnRight();
                moveForward();
                if(::orientation == 1){
                    ::y = ::y - 1;
                    ::orientation = 3;
                }

                if(::orientation == 2){
                    ::x = ::x - 1;
                    ::orientation = 0;

                }
                if(::orientation == 3){
                    ::y = ::y + 1;
                    ::orientation = 1;
                }
                if(::orientation == 0){
                    ::x = ::x + 1;
                    ::orientation = 2;
                }

                A = false;
                B = false;
            }
            A = false;
            B = false;

        }
   }
}
//printUI(std::to_string(orientation).c_str());

