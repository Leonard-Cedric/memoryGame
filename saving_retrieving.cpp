// C++ program to read from a file 
#include <fstream> 
#include <iostream> 
#include <string>
#include <ctime>
#include <array>

using namespace std; 


int main() 
{ 
    string playerName[3]={"","",""};
    int highScores[3]= {0,0,0};

    ifstream inputScoreFile("scores.txt");

    if (inputScoreFile.is_open()) {
        int counter = 0;
        string name;
        string score;
        while (getline(inputScoreFile, name)) {
            playerName[counter] = name;
            getline(inputScoreFile, score);
            highScores[counter]= stoi(score);
            counter++;
        }

        for (int i= 0 ; i<counter; i++){
            cout << "Player name: " << playerName[i] << "; Score: " << highScores[i] << "\n";
        }
    }


    inputScoreFile.close();
    


    // Writing scores
    ofstream outputScoreFile("scores.txt");
    playerName[1] = "Lordz";
    highScores[1] = 100;

    if (outputScoreFile.is_open()) {
        for(int i= 0; i<5; i++){
            outputScoreFile << playerName[i] << endl;
            outputScoreFile << highScores[i] << endl;
        }
    }
    


    // close the file
    outputScoreFile.close();
    
    return 0; 
}