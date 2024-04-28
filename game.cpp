#include <windows.h>
#include <iostream>


using namespace std;

void gotoXY(int x, int y) ;
void game(int number[]);

int main() {

    int number[] = {12, 7, 8, 9};
    game(number);

    // Example usage
    gotoXY(10, 5);
    cout << "hello World";
    return 0;
}

void gotoXY(int x, int y) {
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void game(int number[]){

    cout << number[0];
}