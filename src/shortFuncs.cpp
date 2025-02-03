#include "../include/shortFuncs.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

// TEST: passed correctly
void makeLower(string& sequence){
    for(auto& ch: sequence){
        if (isalpha(ch)){
            ch = tolower(ch);
        }
    }
}

// TEST: passed correctly
void clearScreen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        system("clear");
    #endif
}

void getCommand(string prompt , string& var){
    cout << '\n' << prompt; 
    getline(cin , var);
    makeLower(var);
}

void welcome(){
    clearScreen();
    cout << "Hey welcome to our project it's MILICH\n";
    cout << "you can buy or sale anything you want !!!\n";
    cout << "Enter 1 for login and if you want to quit any where enter q\n";
}

bool isNumber(string sequence){
    for(char ch : sequence){
        if (!isdigit(ch)){
            return false;
        }
    }
    return true;
}

void quit(){
    clearScreen();
    cout << "I hope you enjoy from this program\n";
    cout << "Back again . Im gonna miss you\n";
}