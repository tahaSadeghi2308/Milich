#include <iostream>
#include "include/users.h"
#include "include/shortFuncs.h"

using namespace std;

int main(){
    welcome();
    string command;
    getCommand("> ", command);
    while(command != "1" && command != "q"){
        clearScreen();
        cout << "Invalid input\n";
        getCommand("> " , command);
    }

    // this if represents if user was loged in
    if (command == "1"){
        clearScreen();
        
        // collect all users
        string username , password;
        User* users = getUserInfoFromFile("../txt_files/users.txt");
        cout << "Here you should enter you username and password\n";
        cout << "If you want to quit enter q in username field\n";
        getCommand("Username: " , username);
        if (username != "q"){
            getCommand("Password: " , password);

            while(!searchInUsers(users , username , password)){
                clearScreen();
                cout << "Invalid login informations , try again!!\n";
                getCommand("Username: " , username);
                if (username != "q"){
                    getCommand("Password: " , password);
                } else {
                    quit();
                    return 0;
                }
            }

            // ===========================================================================
            // since here user logs in correctly
            // write codes when user is login here ....
            clearScreen();
            User currentUser = getUserInfo(users , username , password);
            string prompt = (currentUser.isAdmin) ? "Admin> " : "Normal> ";

            cout << "You logged in successfully !!\n";
            cout << "Now what you want to do ??\n";
            cout << "You can enter help to see what can you do here...\n";
            cout << "If you want to back to the privious page enter back\n";

            string command;
            getCommand(prompt ,command);
            
            if (currentUser.isAdmin){
                // for admin users
                // command handler is this while loop
                while(command != "q"){
                    clearScreen();
                    if (command == "help"){
                        cout << "show                         shows all products\n";
                        cout << "show [product_name]          shows a specific product details\n";
                        cout << "buy [product_name] [count]   you can buy a product with this\n";
                        cout << "balance                      shows your wallet balance\n";
                    } else if (command == "show"){
                        // show all products here...
                    } else {
                        cout << "Invalid command entered!!\n";
                    }
                    getCommand(prompt , command);
                }
                quit();
                return 0;
            } else {
                // for normal users
            }

        } else {
            quit();
            return 0;
        }
    } else if (command == "q"){
        quit();
        return 0;
    }
    return 0;
}
