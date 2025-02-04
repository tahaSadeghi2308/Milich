#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <string>
using namespace std;

// variables
const short USERS_COUNT = 5;

// structures
struct User {
    int id;
    string username;
    string password;
    bool isAdmin;
    int walletAmount;
};

// functions
User* getUserInfoFromFile(string );
bool searchInUsers(User* , string , string);
bool isAdminUser(User* , string);
User getUserInfo(User* , string , string );
void updateUsersInfo(string , User* );

#endif
