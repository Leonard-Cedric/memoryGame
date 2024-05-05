// C++ program to read from a file 
#include <fstream> 
#include <iostream> 
#include <string>
#include <ctime>
#include <array>

using namespace std; 

bool is_number_exist(int arr[], int index_pointer, int number){
    bool exist= false;

    for(int i= 0; i<=index_pointer; i++){ 
       if (arr[i]==number)
        return true;
    }

    return exist;
}

int random_number(int max, int divisor){
    int num;
    do{
        num= rand() % divisor;
    }while(num >= max);

    return num;
}

int main() 
{ 
    int const ARRAY_SIZE= 5;
    int const MAX_NUM= 100;
    
    srand(time(0));

    // Open the input file named "words.txt" 
    ifstream sourceFile("words.txt"); 
  
    // Check if the file is successfully opened 
    if (!sourceFile.is_open()) { 
        cerr << "Error opening the file!" << endl; 
        return 1; 
    } 
  
    int counter = 0;
    string line; // Declare a string variable to store each line of the file 
    string words[MAX_NUM];

    // Read each line of the file and print it to the standard output stream 
    while (getline(sourceFile, line)) {
         words[counter++]= line;
    }

    int divisor = 100;
    int arr_max_index = counter;
    int arr_random_index[ARRAY_SIZE] = {-1,-1,-1,-1,-1};

    for(int i=0; i<ARRAY_SIZE; i++){
        int number;
        do{
            number= random_number(arr_max_index, divisor);
        }while (is_number_exist(arr_random_index, i, number));

        arr_random_index[i] = number;
    }

    for(int j=0; j<ARRAY_SIZE; j++){
        cout << "word[" << arr_random_index[j] << "]: " << words[arr_random_index[j]] << "\n"; 
    }

    //==============================
    int max_num = 100;
    int arr_random_num[ARRAY_SIZE] = {-1,-1,-1,-1,-1};

    for(int i=0; i<ARRAY_SIZE; i++){
        int number;
        do{
            number= random_number(max_num, max_num);
        }while (is_number_exist(arr_random_num, ARRAY_SIZE, number));

        arr_random_num[i] = number;
    }

    for(int j=0; j<ARRAY_SIZE; j++){
        cout << "[" << j << "]: " << arr_random_num[j]<< "\n" ; 
    }

    // Close the file 
    sourceFile.close(); 
  
    return 0; 
}