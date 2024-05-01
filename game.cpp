#include <iostream>
#include <windows.h>
#include <stdlib.h> 

using namespace std;

void box(int width, int length);
void gotoXY(int x, int y) ;
void game(int number[]);



int main() {

    system("cls");
    box(50,7);
    gotoXY(25, 4);

    int number[] = {12, 7, 8, 9};
    game(number);

    gotoXY(0, 10);
    return 0;
}


void game(int number[]){

    cout << number[0];
}

void box(int width, int length){
    system("Color 0A");
    int x=0;
    int y=0;
    char symbol= ' ';

    for(int i=1; i<=8; i++){
        int numPrinted=0;
        int numToPrint=1;
        switch (i){
            case 1:
            case 5:
                symbol = char(205);
                numToPrint = width;
                break;
            case 3:
            case 7:
                symbol = char(186);
                numToPrint = length;
                break;
            case 2:
                symbol = char(187);                
                break;
            case 4:
                symbol = char(188);
                break;
            case 6:    
                symbol = char(200);
                break;  
            case 8:    
                symbol = char(201);
                break;                
        }
        
        while (numPrinted != numToPrint)
        {
            switch (i)
            {
                case 1:
                case 2:
                    x++;
                    break;
                case 3:
                case 4:
                    y++;
                    break;
                case 5:
                case 6:
                    x--;
                    break;
                case 7:
                case 8:
                    y--;
                    break;
            }
            gotoXY(x, y);
            cout << symbol;
            Sleep(5);
            numPrinted++;
        }
    }
}

void gotoXY(int x, int y) {
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}