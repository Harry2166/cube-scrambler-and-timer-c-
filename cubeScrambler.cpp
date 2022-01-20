#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>

using namespace std;

// stopwatch code (with some revisions) from: https://www.codespeedy.com/cpp-program-to-create-a-stopwatch/
void stopwatch();
//  file opening code from: https://stackoverflow.com/questions/4155537/writing-into-a-text-file-without-overwriting-it & https://www.cplusplus.com/doc/tutorial/files/
void fileOpen(int hour, int minute, int second);
void scrambler(int number, string scramble[]); // creates the scramble

int main(){

    srand((unsigned) time(0));
    
    char answer;
    int random, exit_code = 10;

    do {
        random = (rand() % 25) + 1; // randomly generates a number that is from 1 to 25
    } while (random < 20); // makes it loop until "random" is between 21 and 25

    string nincompoop[random]; // char array for the scramble

    scrambler(random, nincompoop);

    cout << "\nEnter y if you want to start solving, \n";
    cout << "Enter q if you want to quit\n";

    cin >> answer;

    if(answer == 'y'){
        stopwatch();
    } else if (answer == 'q'){
        _Exit(10);
    } else{
        cout << "Please enter the valid key.";
        cin >> answer;
    }

    return 0;
}

void scrambler(int number, string scramble[]){

    srand((unsigned) time(0));

    string moves[] = {"R", "L", "U", "D", "B"}; // move type 1
    string moves_prime[] = {"R'", "L'", "U'", "D'", "B'"}; // move type 2
    string moves_double[] = {"R2", "L2", "U2", "D2", "B2"}; // move type 3

    int index[number]; // where the indices will be stored

    int movePicker; // this integer picks a number from 0 to 4, which are the indices for the moves

    for(int i = 0; i < number; i++){
        int moveTypePicker = (rand() % 3) + 1; // randomly picks a number from 1 to 3
        index[i] *= 0;
        switch(moveTypePicker){
            case 1:

                do { movePicker = (rand() % 5);
                } while(index[i-1] == movePicker); // loops through until the index is different from the previous index in order to avoid unnecessary cancellation/doubling of move
                
                scramble[i] += moves[movePicker];
                index[i] += movePicker;
                break;

            case 2:
                do { movePicker = (rand() % 5);
                } while(index[i-1] == movePicker); // refer to line 68
                
                scramble[i] += moves_prime[movePicker];
                index[i] += movePicker;
                break;

            case 3:
                do { movePicker = (rand() % 5);
                } while(index[i-1] == movePicker); // refer to line 68

                scramble[i] += moves_double[movePicker];
                index[i] += movePicker;
                break;
        }
    }
    
    for(int i = 0; i < number; i++){
        cout << scramble[i] << " ";
    }

}

void stopwatch(){

    system("CLS");
    int HH=0,MM=0,SS=0;
    cout<<"\n\t\t Solving Time:";
    cout<<"\n\t\t HH: MM: SS";
    cout<<"\n\t\t "<<HH<<" : "<<MM<<" : "<<SS;
    cout<<"\n\t\t press any key to start";
    _getch();
    while(!_kbhit())
    {
        SS++;
        Sleep(1000);
    if(SS>59)
    {
        MM++;
        SS=0;
    }
    if(MM>59)
    { 
        HH++;
        MM=0;
    }
    system("CLS");
    cout<<"\n\t\t Solving Time:";
    cout<<"\n\t\t HH: MM: SS";
    cout<<"\n\t\t "<<HH<<" : "<<MM<<" : "<<SS;
    cout<<"\n\t\t press any key to stop";
    }
    _getch();
    cout<<"\n\t\t the time solving is";
    cout<<"\n\t\t "<<HH<<" : "<<MM<<" : "<<SS;
    _getch();

    fileOpen(HH, MM, SS);
}

void fileOpen(int hour, int minute, int second){
    ofstream myfile;
    myfile.open("TimeSaver.txt", fstream::app);
    myfile << hour << ":" << minute << ":" << second << "\n";
    myfile.close();
}