#include <iomanip>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
using namespace std;
void mainGame(); 
void mainMenu();

void shuffleArr(string arrayOne[], int sizeOf) {
    for (int i = 0; i < sizeOf; i++) {
        int index = rand() % sizeOf;
        string temp = arrayOne[i];
        arrayOne[i] = arrayOne[index];
        arrayOne[index] = temp;
    }
}


string DisplayArr[4][4] ={""}; 
string DisplayArr6[6][6] = { "" };
string DisplayArr8[8][8] = { "" }; 
bool arrayMatch[4][4] = { false };
bool arrayMatch6[6][6] = { false };
bool arrayMatch8[8][8] = { false };

string themesArr[16]; string themesTwo[4][4]; string themesArrayM[36]; string themesTwoM[6][6];
string themesArrayL[64]; string themesArrTwoL[8][8];
int rowPick, columnPick, rowPick2, columnPick2, gameEnd, gameScore = 0; int gameTries = 0;
int boardSize, difficulty;
int gridSize = 0, themeChoice;


int boardFunct(int & boardSize) {
    switch (boardSize) {
    case 1:
        boardSize = 4;
        break;
    case 2:
        boardSize = 6;
        break;
    case 3:
        boardSize = 8;
        break;
    default:
        cout << "You entered an invalid choice, try again..." << endl; 
        Sleep(2000);
        system("cls");
        mainMenu();
    }
    return boardSize;
}

int diffultyFunc(int difficulty) {
    switch (difficulty) {
    case 1:
        difficulty = 6000;
        break;
    case 2:
        difficulty = 4000;
        break;
    case 3:
        difficulty = 2000;
        break;
    default:
        cout << "You entered an invalid choice, try again..." << endl;
        Sleep(2000);
        system("cls");
        mainMenu();
    }
    return difficulty;
}

void mainMenu() {
    ifstream myFile;
    cout << "------MAIN GAME MENU------" << endl << endl; 
    cout << "Welcome To the Memory Matching Game!!" << endl << endl; 
    cout << "Select 1 for New Game, or 2 to Exit: " << endl;
    cin >> gameEnd;
    if (gameEnd == 1) {
        cout << "You will select theme, difficulty, and size of grid!" << endl;
        cout << "Select Theme for Game" << endl;
        cout << "Press 1 for Names: " << endl;
        cout << "Press 2 for States: " << endl;
        cout << "Press 3 for Trees: " << endl;
        cin >> themeChoice;
        cout << "Select Size of Grid:" << endl << "1 = Small " << endl;
        cout << "2 = Medium " << endl << "3 = Large" << endl;
        cin >> boardSize;
        boardSize = boardFunct(boardSize);
        cout << "Select Difficulty:" << endl << "1 = Easy(6 second display)" << endl;
        cout << "2 = Medium(4 seconds)" << endl << "3 = Hard(2 second display)" << endl;
        cin >> difficulty;
        difficulty = diffultyFunc(difficulty);
        system("cls");
        mainGame();
    }
    else {
        cout << "Thank You for playing, Goodbye" << endl;
    }
}


void mainGame(){
    ifstream myFile;
    switch (themeChoice) {
    case 1:
        myFile.open("Week10BrettSullivan50NamesFile2.txt");
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize;j++) {
                DisplayArr[i][j] = "names";
                DisplayArr6[i][j] = "names";
                DisplayArr8[i][j] = "names";
            }
        }
        break;
    case 2:
        myFile.open("Week10BrettSullivan50StatesFile1.txt");
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize;j++) {
                DisplayArr[i][j] = "States";
                DisplayArr6[i][j] = "States";
                DisplayArr8[i][j] = "States";
            }
        }
        break;
    case 3:
        myFile.open("Week10BrettSullivan50TreesFile3.txt");
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                DisplayArr[i][j] = "Trees";
                DisplayArr6[i][j] = "Trees";
                DisplayArr8[i][j] = "Trees";
            }
        }
        break;
    default:
        cout << "Wrong Selection, try again..." << endl;
        Sleep(2000);
        system("cls");
        mainMenu();
    }
    if (boardSize == 4) {
        for (int i = 0; i < 8; i++) {
            string strInput;
            getline(myFile, strInput);
            themesArr[2 * i] = strInput;
            themesArr[2 * i + 1] = strInput;

        }
        shuffleArr(themesArr, 16);
        int curr = 0;
        int row = 0;
        for (int i = 0; i < 4; i++) {
            cout << setw(5);
            for (int j = 0; j < 4; j++) {
                themesTwo[i][j] = themesArr[curr++];
                //cout << setw(5) << themesTwo[i][j];
            }
            cout << endl; 
        }

        while (gameTries <= 8) {

            cout << "--------------column 0-column 1-column 2-column 3" << endl;
            for (int i = 0; i < 4; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 4; j++) {
                    if (arrayMatch[i][j] == false) {
                        cout << setw(5);
                        cout << setw(5) << "|" << DisplayArr[i][j];
                    }
                    else {
                        DisplayArr[i][j] = themesTwo[i][j];
                        cout << setw(5) << "|" << themesTwo[i][j];
                    }
                }
                cout << setw(5) << endl;
            }
            cout << "Your current gamescore is: " << gameScore << endl;
            cout << "Type Row and Column numbers to reveal guesses: " << endl;
            cout << "Pick First Element: " << endl; cout << "Row: ";
            cin >> rowPick;
            cout << "Column: "; cin >> columnPick;
            cout << "Pick matching element: " << endl;
            cout << "Row: "; cin >> rowPick2;
            cout << "Column: "; cin >> columnPick2;
            if (rowPick == rowPick2 && columnPick == columnPick2) {
                cout << "You cant pick the same thing for both elements!" << endl;
                cout << "Goodbye, next time dont cheat..." << endl;
                Sleep(2000);
                system("cls");
                mainMenu();
            }
            if (themesTwo[rowPick][columnPick] == themesTwo[rowPick2][columnPick2]) {
                arrayMatch[rowPick][columnPick] = true;
                arrayMatch[rowPick2][columnPick2] = true;
                cout << "Congrats You found a match!" << endl;
                gameScore++;
            }
            gameTries++;

            cout << "--------------column 0-column 1-column 2-column 3" << endl;
            for (int i = 0; i < 4; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 4; j++) {
                    if ((i == rowPick) && (j == columnPick)) {
                        cout << setw(5) << "|" << themesTwo[i][j];
                    }
                    if ((i == rowPick2) && (j == columnPick2)) {
                        cout << setw(5) << "|" << themesTwo[i][j];
                    }
                    else {
                        cout << setw(5) << "|" << DisplayArr[i][j];
                    }
                }

                cout << endl;
            }

            Sleep(difficulty);
            system("cls");

            if (gameScore > 6) {
                cout << "You Won! game over" << endl << endl;
                mainMenu();
            }
            else if (gameTries > 8) {
                cout << "You did not find enough matches :(..." << endl;
                Sleep(difficulty);
                system("cls");
                mainMenu();
            }
        }
        myFile.close();
    }
    if (boardSize == 6) {
        for (int i = 0; i < 36; i++) {
            string strInput;
            getline(myFile, strInput);
            themesArrayM[2 * i] = strInput;
            themesArrayM[2 * i + 1] = strInput;

        }
        shuffleArr(themesArrayM, 36);
        int curr = 0;
        int row = 0;
        for (int i = 0; i < 6; i++) {
            cout << setw(5) << "row" << setw(5) << row;
            row++;
            for (int j = 0; j < 6; j++) {
                cout << setw(5);
                themesTwoM[i][j] = themesArrayM[curr++];
                cout << setw(5) << themesTwoM[i][j];
            }
            cout << endl;
        }

        while (gameTries <= 8) {

            cout << "--------------column 0-column 1-column 2-column 3-column 4-column-5" << endl;
            for (int i = 0; i < 6; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 6; j++) {
                    if (arrayMatch6[i][j] == false) {
                        cout << setw(5);
                        cout << setw(5) << "|" << DisplayArr6[i][j];
                    }
                    else {
                        DisplayArr6[i][j] = themesTwoM[i][j];
                        cout << setw(5) << "|" << themesTwoM[i][j];
                    }
                }
                cout << setw(5) << endl;
            }
            cout << "Your current gamescore is: " << gameScore << endl;
            cout << "Type Row and Column numbers to reveal guesses: " << endl;
            cout << "Pick First Element: " << endl; cout << "Row: ";
            cin >> rowPick;
            cout << "Column: "; cin >> columnPick;
            cout << "Pick matching element: " << endl;
            cout << "Row: "; cin >> rowPick2;
            cout << "Column: "; cin >> columnPick2;
            if (rowPick == rowPick2 && columnPick == columnPick2) {
                cout << "You cant pick the same thing for both elements!" << endl;
                cout << "Goodbye, next time dont cheat..." << endl;
                Sleep(2000);
                system("cls");
                mainMenu();
            }
            if (themesTwoM[rowPick][columnPick] == themesTwoM[rowPick2][columnPick2]) {
                arrayMatch6[rowPick][columnPick] = true;
                arrayMatch6[rowPick2][columnPick2] = true;
                cout << "Congrats You found a match!" << endl;
                gameScore++;
            }
            gameTries++;

            cout << "--------------column 0-column 1-column 2-column 3" << endl;
            for (int i = 0; i < 6; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 6; j++) {
                    if ((i == rowPick) && (j == columnPick)) {
                        cout << setw(5) << "|" << themesTwoM[i][j];
                    }
                    if ((i == rowPick2) && (j == columnPick2)) {
                        cout << setw(5) << "|" << themesTwoM[i][j];
                    }
                    else {
                        cout << setw(5) << "|" << DisplayArr6[i][j];
                    }
                }

                cout << endl;
            }

            Sleep(difficulty);
            system("cls");

            if (gameScore > 4) {
                cout << "You Won! game over" << endl << endl;
                mainMenu();
            }
            else if (gameTries > 8) {
                cout << "You did not find enough matches :(..." << endl;
                Sleep(difficulty);
                system("cls");
                mainMenu();
            }
        }
        myFile.close();

    }
    if (boardSize == 8) {
        for (int i = 0; i < 32; i++) {
            string strInput;
            getline(myFile, strInput);
            themesArrayL[2 * i] = strInput;
            themesArrayL[2 * i + 1] = strInput;

        }
        shuffleArr(themesArrayL, 64);
        int curr = 0;
        int row = 0;
        for (int i = 0; i < 8; i++) {
            //cout << setw(5) << "row" << setw(5) << row;
            row++;
            for (int j = 0; j < 8; j++) {
                //cout << setw(5);
                themesArrTwoL[i][j] = themesArrayL[curr++];
                //cout << setw(5) << themesArrTwoL[i][j];
            }
            //cout << endl;
        }

        while (gameTries <= 8) {

            cout << "--------------column 0-column 1-column 2-column 3-column 4-column-5-column-6-column-7" << endl;
            for (int i = 0; i < 8; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 8; j++) {
                    if (arrayMatch8[i][j] == false) {
                        cout << setw(5);
                        cout << setw(5) << "|" << DisplayArr8[i][j];
                    }
                    else {
                        DisplayArr8[i][j] = themesArrTwoL[i][j];
                        cout << setw(5) << "|" << themesArrTwoL[i][j];
                    }
                }
                cout << setw(5) << endl;
            }
            cout << "Your current gamescore is: " << gameScore << endl;
            cout << "Type Row and Column numbers to reveal guesses: " << endl;
            cout << "Pick First Element: " << endl; cout << "Row: ";
            cin >> rowPick;
            cout << "Column: "; cin >> columnPick;
            cout << "Pick matching element: " << endl;
            cout << "Row: "; cin >> rowPick2;
            cout << "Column: "; cin >> columnPick2;
            if (rowPick == rowPick2 && columnPick == columnPick2) {
                cout << "You cant pick the same thing for both elements!" << endl;
                cout << "Goodbye, next time dont cheat..." << endl;
                Sleep(2000);
                system("cls");
                mainMenu();
            }
            if (themesArrTwoL[rowPick][columnPick] == themesArrTwoL[rowPick2][columnPick2]) {
                arrayMatch8[rowPick][columnPick] = true;
                arrayMatch8[rowPick2][columnPick2] = true;
                cout << "Congrats You found a match!" << endl;
                gameScore++;
            }
            gameTries++;

            cout << "--------------column 0-column 1-column 2-column 3" << endl;
            for (int i = 0; i < 8; i++) {
                cout << setw(5) << "row" << setw(5) << i;
                for (int j = 0; j < 8; j++) {
                    if ((i == rowPick) && (j == columnPick)) {
                        cout << setw(5) << "|" << themesArrTwoL[i][j];
                    }
                    if ((i == rowPick2) && (j == columnPick2)) {
                        cout << setw(5) << "|" << themesArrTwoL[i][j];
                    }
                    else {
                        cout << setw(5) << "|" << DisplayArr8[i][j];
                    }
                }

                cout << endl;
            }

            Sleep(difficulty);
            system("cls");

            if (gameScore > 2) {
                cout << "You Won! game over" << endl << endl;
                mainMenu();
            }
            else if (gameTries > 10) {
                cout << "You did not find enough matches :(..." << endl;
                Sleep(difficulty);
                system("cls");
                mainMenu();
            }
        }
        myFile.close();

    }
}


 int main() {
     cout << "Brett Sullivan-5-21-2021" << endl; 
     srand(time(NULL));
     mainMenu();
    }



