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
int game_word(int arr_delay[], int arr_score_level[]);

void genNum(int arr[], int index_pointer, int maxNum, int divisor);
bool is_number_exist(int arr[], int arra_size, int number);
int random_number(int max, int divisor);

void displayNum(int arr_random_num[], int arr_size, int level, int arr_delay[]);
void displayWord(string words[], int arr_random_index[], int arr_size, int level, int arr_delay[]);

int get_num_score(int arr_random_num[], int arr_size, int level, int arr_score_level[]);
int get_word_score(string words[], int arr_random_index[], int arr_size, int level, int arr_score_level[]);

void show_score(int score_num, int level);
void show_player_score(string player, int final_score);

int openFile(string words[]);
void display (int column, int row, string message);
void box(int width, int length, bool hasDelay);
void gotoXY(int x, int y) ;

int const MAX_LEVEL = 1;
int const ARRAY_SIZE = 5;
int const MAX_NUM= 100;
int const DIVISOR= 100;
                                
int main() {

    int player_score = 0;
    
    int arr_delay_num[] = {2000, 1500, 1000, 800, 500};
    int arr_delay_words[] = {2500, 1800, 1500, 900, 600};
    int arr_score_level[] = {10, 20, 30, 40, 50};
    
    srand(time(0));
    
    char ans;
    do{
        box(50,7, true);
        string playerName = welcome_part();
        
        box(50,7,false);
        int mode = pickMode();
        
        box(50,7,false);
        switch(mode){
            case 1:
                player_score = game_num(arr_delay_num, arr_score_level);
                break;
            case 2:
                player_score = game_word(arr_delay_words, arr_score_level);
                break;
        }
        show_player_score(playerName, player_score);
        gotoXY(0, 10);

        cout << "Do you want to Play Again? [Y/N] ";
        cin >> ans;
    }while (ans == 'y' || ans == 'Y');

    return 0;
}

string welcome_part(){
    string playerName;
    display(14,3, "Welcome to Memory Game");
    display(5,6, "Enter Player name: ");
    cin >> playerName;
    return playerName;
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
    for(int level = 0; level < MAX_LEVEL; level++){
        int arr_random_num[]= {-1,-1,-1,-1,-1};
        genNum(arr_random_num, ARRAY_SIZE, MAX_NUM, DIVISOR);
        displayNum(arr_random_num, ARRAY_SIZE, level, arr_delay);
        player_score += get_num_score(arr_random_num, ARRAY_SIZE, level, arr_score_level);
        show_score(player_score, level);
    }
    return player_score;
}

int game_word (int arr_delay[], int arr_score_level[]){
    string words[MAX_NUM];
    int player_score= 0;
    int max_index_ctr = openFile(words);
    
    for(int level = 0; level < MAX_LEVEL; level++){
        int arr_random_index[]= {-1,-1,-1,-1,-1};
        genNum(arr_random_index, ARRAY_SIZE, max_index_ctr, DIVISOR);
        displayWord(words, arr_random_index, ARRAY_SIZE, level, arr_delay);
        player_score += get_word_score(words, arr_random_index, ARRAY_SIZE, level, arr_score_level);
        show_score(player_score, level);
    }
    return player_score;
}

void genNum(int arr[], int array_size, int maxNum, int divisor) {
    
    for(int i=0; i<array_size; i++){
        int number;
        do{
            number= random_number(maxNum, divisor);
        }while (is_number_exist(arr, i, number));

        arr[i] = number;
    }
}

int random_number(int max, int divisor){
    int num;
    do{
        num= rand() % divisor;
    }while(num > max);

    return num;
}

bool is_number_exist(int arr[], int index_pointer, int number){
    bool exist= false;

    for(int i= 0; i<index_pointer; i++){ 
       if (arr[i]==number)
        return true;
    }

    return exist;
}

void displayNum(int arr_random_num[], int arr_size, int level, int arr_delay[]) {
    for(int i=0; i<arr_size; i++) {
        display(25, 4, to_string(arr_random_num[i]));
        gotoXY(0, 10);
        Sleep(arr_delay[level]);
        display(25, 4, "          ");
    }
}

void displayWord(string words[], int arr_random_index[], int arr_size, int level, int arr_delay[]){
    for(int i=0; i<arr_size; i++) {
        display (22, 4, words[arr_random_index[i]]);
        gotoXY(0, 10);
        Sleep(arr_delay[level]);
        display(25, 4, "          ");
    }
}


int get_num_score(int arr_random_num[], int arr_size, int level, int arr_score_level[]){
    int guess_num[arr_size];
    int score_num = 0;
    display (12, 2, "Enter numbers seen in order:");
    
    gotoXY(17, 4);
    for (int i = 0; i < arr_size; i++){
        cin >> guess_num[i];
    }
    for (int j = 0; j < arr_size; j++){
        if (arr_random_num[j] == guess_num[j]){
            score_num += arr_score_level[level];
        }
    }
    
    box(50,7,false);
    return score_num;
}

int get_word_score(string words[], int arr_random_index[], int arr_size, int level, int arr_score_level[]){
    string guess_word[arr_size];
    int score = 0;
    box(50,7,false);
    display (12, 2, "Enter words seen in order:");
    
    gotoXY(8, 4);
    for (int i = 0; i < arr_size; i++){
        cin >> guess_word[i];
    }

    for (int j = 0; j < arr_size; j++){
        if (words[arr_random_index[j]] == guess_word[j]){
            score += arr_score_level[level];
        }
    }

    box(50,7,false);
    return score;
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

void show_player_score(string player, int final_score){
    box(50,7,false);
    display (18, 2, "Congratulations!  "); 
    display (25, 3,  player);
    display (15, 6, "Your final score is " + to_string (final_score));
    gotoXY (0,10);
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