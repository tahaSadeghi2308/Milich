#ifndef SHORTFUNCS_H
#define SHORTFUNCS_H

#include <string>
#include "productManager.h"
#include "usersManager.h"
using namespace std;

// functions
void makeLower(string& );
void clearScreen();
void getCommand(string , string& );
void welcome();
bool isNumber(string );
void quit();
void releseAllMems(User** , Product**);
string deleteSpace(string );

#endif