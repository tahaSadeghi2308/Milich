#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/usersManager.h"

using namespace std;

// TEST:  passed right !!!
User* getUserInfoFromFile(string fileAddress){

    // make sure u free this memory
    User* allUsers = new User[5];

    ifstream file;
    file.open(fileAddress);

    int i = 0;
    if(file.is_open()){
        while(!file.eof()){
            User user;
            stringstream lineInfo;

            // read entire line
            string line;
            getline(file , line);
            if (line != ""){
                lineInfo.str(line);

                string id , isAdmin , walletAmount;
                lineInfo >> id;

                user.id = stoi(id);
                lineInfo >> user.username;
                lineInfo >> user.password;

                lineInfo >> isAdmin;
                user.isAdmin = stoi(isAdmin);

                lineInfo >> walletAmount;
                user.walletAmount = stoi(walletAmount);

                allUsers[i++] = user;
            }
        }
        file.close();
    } else {
        cout << "System can't open the file\n";
        delete[] allUsers;
        allUsers = nullptr;
    }
    return allUsers;
}

// TEST: passed correctly
bool searchInUsers(User* usersList , string username , string password){
    for(short i {0}; i < USERS_COUNT; i++){
        if(usersList[i].username == username && usersList[i].password == password){
            return true;
        }
    }
    return false;
}

// TEST: passed correctly
bool isAdminUser(User* usersList, string username){
    for(short i {0}; i < USERS_COUNT; i++){
        if(usersList[i].username == username){
            if(usersList[i].isAdmin){
                return true;
            }
        }
    }
    return false;
}

User getUserInfo(User* usersList , string username , string password){
    for(short i {0}; i < USERS_COUNT; i++){
        if(usersList[i].username == username && usersList[i].password == password){
            return usersList[i];
        }
    }
}

void updateUsersInfo(string fileAddress , User* usersList){
    ofstream file;
    file.open(fileAddress);
    if(file.is_open()){
        for(short i {0}; i < USERS_COUNT; i++){
            file << usersList[i].id << " "
                 << usersList[i].username << " "
                 << usersList[i].password << " "
                 << usersList[i].isAdmin << " " 
                 << usersList[i].walletAmount << '\n';
            file.close();
        }
    } else {
        cout << "Couldn't open file!!\n";
    }
}
