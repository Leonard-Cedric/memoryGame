#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <fstream> 
#include <ctime>
#include <array>
#include <string>
#include <conio.h>

using namespace std;

string welcome_part();
int pickMode ();
int game_num(int arr_delay[], int arr_score_level[]);
void game_word ();
void box(int width, int length, bool hasDelay);
void gotoXY(int x, int y) ;
bool is_number_exist(int arr[], int arra_size, int number);
int random_number(int max, int divisor);
void genNum(int arr[], int array_size, int maxNum, int divisor);
int openFile(string words[]);
void displayNum(int arr[], int arr_size, int level, int arr_delay[]);
void displayWord(string words[], int arr[], int arr_size, int level);
int get_num_score(int arr[], int arr_size, int level, int arr_score_level[]);
void show_score(int score_num, int level);
void highest_score(string player_name, int score_num);
void display (int column, int row, string message);

int const MAX_LEVEL = 5;
int const ARRAY_SIZE = 5;
int const MAX_NUM= 100;
int const DIVISOR= 100;

int main() {

    int player_score = 0;
    
    int arr_delay_num[] = {2000, 1500, 1000, 800, 500};
    int arr_delay_words[] = {4000, 3000, 2000, 1000, 500};
    int arr_score_level[] = {10, 20, 30, 40, 50};
    
    srand(time(0));
    
    box(50,7, true);
    string playerName = welcome_part();
    
    box(50,7,false);
    int mode = pickMode();

    box(50,7,false);
    switch(mode){
        case 1:
            player_score = game_num(arr_delay_num, arr_score_level);
            // for(int i = 0; i < MAX_LEVEL; i++){
            //     int arr_random_num[]= {-1,-1,-1,-1,-1};
            //     genNum(arr_random_num, ARRAY_SIZE, MAX_NUM, DIVISOR);
            //     displayNum(arr_random_num, ARRAY_SIZE, i, arr_delay_num);
            //     player_score += get_num_score(arr_random_num, ARRAY_SIZE, i, arr_score_level);
            //     show_score(player_score, i);
            // }
            break;
        case 2:
            string words[MAX_NUM];
            int arr_max_index = openFile(words);

            for(int i = 0; i < MAX_LEVEL; i++){
                int arr_random_index[]= {-1,-1,-1,-1,-1};
                genNum(arr_random_index, arr_max_index, MAX_NUM, DIVISOR);
                displayWord(words, arr_random_index, ARRAY_SIZE, i);
                player_score += get_num_score(arr_random_index, ARRAY_SIZE, i, arr_score_level);
                show_score(player_score, i);
            }
            break;
    }

    highest_score(playerName, player_score);
    gotoXY(0, 25);
    return 0;
}



int pickMode (){
    int mode;
    do{
        box(50,7,false);
        display (2,2,"Mode: ");
        display (4,3, "1 - Number");
        display (4,4, "2 - Words");

        display(2,6, "Select Mode [1 or 2]: ");
        cin >> mode;

    }while( mode != 1 && mode != 2);

    return mode;
}

int game_num(int arr_delay[], int arr_score_level[]){
    int player_score= 0;
    for(int i = 0; i < MAX_LEVEL; i++){
        int arr_random_num[]= {-1,-1,-1,-1,-1};
        genNum(arr_random_num, ARRAY_SIZE, MAX_NUM, DIVISOR);
        displayNum(arr_random_num, ARRAY_SIZE, i, arr_delay);
        player_score += get_num_score(arr_random_num, ARRAY_SIZE, i, arr_score_level);
        show_score(player_score, i);
    }
    return player_score;
}

void game_word (){

}

string welcome_part(){
    string playerName;
    display(14,3, "Welcome to Memory Game");
    display(5,6, "Enter Player name: ");
    cin >> playerName;
    return playerName;
}


bool is_number_exist(int arr[], int array_size, int number){
    bool exist= false;

    for(int i= 0; i<array_size; i++){ 
       if (arr[i]==number)
        return true;
    }

    return exist;
}

int random_number(int max, int divisor){
    int num;
    do{
        num= rand() % divisor;
    }while(num > max);

    return num;
}

int openFile(string words[]) {
    // Open the input file named "words.txt"
    ifstream inputFile("words.txt");

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return -1;
    }
    int counter = 0;
    string line;

    while (getline(inputFile, line)) {
         words[counter++]= line;
    }

    return counter - 1;
}

void genNum(int arr[], int array_size, int maxNum, int divisor) {
    
    for(int i=0; i<array_size; i++){
        int number;
        do{
            number= random_number(maxNum, divisor);
        }while (is_number_exist(arr, array_size, number));

        arr[i] = number;
    }
}

void displayNum(int arr[], int arr_size, int level, int arr_delay[]) {
    for(int i=0; i<arr_size; i++) {
        gotoXY(25,4);
        cout << arr[i];
        Sleep(arr_delay[level]);
        gotoXY(25,4);
        cout << "          ";
    }
}

void displayWord(string words[], int arr[], int arr_size, int level){

}

int get_num_score(int arr[], int arr_size, int level, int arr_score_level[]){
    int guess_num[arr_size];
    int score_num = 0;
    display (12, 2, "Enter numbers seen in order:");
    
    gotoXY(17, 4);
    for (int i = 0; i < arr_size; i++){
        cin >> guess_num[i];
    }
    for (int j = 0; j < arr_size; j++){
        if (arr[j] == guess_num[j]){
            score_num += arr_score_level[j];
        }
    }
    
    box(50,7,false);
    return score_num;
}

void show_score(int score_num, int level) {
    display (19, 4, "Score: " + to_string(score_num));
    Sleep(2000);
    
    box(50,7,false);
    if (level < 4) {
        display (16, 2, "Ready for Level " + to_string(level + 2));
        display (11, 6, "Press enter key to continue.");
        getch();
    }
    
    box(50,7,false);
}

 void highest_score(string player_name, int score_num) {
//     display (1,2);
//     cout << "Highest Scores: ";
//     display(1,4);
//     cout << "#1. " << player_name << " - " << score_num << " pts.";
//     display(1,5);
//     cout << "#2. ";
//     display(1,6);
//     cout << "#3. ";
 }

void display (int column, int row, string message){
    gotoXY (column,row);
    cout << message;
}

void box(int width, int length, bool hasDelay){
    system("cls");
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
            if (hasDelay)
                Sleep(5);

            numPrinted++;
        }
    }
    gotoXY(25, 4);
}

void gotoXY(int x, int y) {
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}