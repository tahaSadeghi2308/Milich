#include <iostream>
#include <iomanip>
#include "include/usersManager.h"
#include "include/shortFuncs.h"
#include "include/productManager.h"

using namespace std;

int main(){
    welcome();
    string command;
    getCommand("> ", command);
    while(deleteSpace(command) != "1" && deleteSpace(command) != "q"){
        clearScreen();
        cout << "Invalid input\n";
        getCommand("> " , command);
    }

    // this if represents if user was loged in
    if (deleteSpace(command) == "1"){
        clearScreen();
        
        // collect all users
        string username , password;
        User* users = getUserInfoFromFile("../txt_files/users.txt");
        cout << "Here you should enter you username and password\n";
        cout << "If you want to quit enter q in username field\n";
        getCommand("Username: " , username);
        if (deleteSpace(username) != "q"){
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
            // ------------ products and their count -----------------------
            int productsCount , currentArrayLen;
            Product* allPro = getAllProducts("../txt_files/products.txt" , productsCount , currentArrayLen);
            // ---------------------------------------------------------------------
            cout << "You logged in successfully !!\n";
            cout << "Now what you want to do ??\n";
            cout << "You can enter help to see what can you do here...\n";
            cout << "If you want to back to the privious page enter back\n";

            string command;
            getCommand(prompt ,command);
            
            if (currentUser.isAdmin){
                // for admin users
                // command handler is this while loop
                
            } else {
                // for normal users
                // command handler is while loop
                while(deleteSpace(command) != "q"){
                    clearScreen();
                    if (deleteSpace(command) == "balance"){
                        cout << "Your balance now is " << currentUser.walletAmount << '\n';
                    } else if (deleteSpace(command) == "show"){
                        cout << setw(12) << "Product Name" << setw(12) << "Amount" << setw(12) << "Price\n";
                        for(int i = 0; i < productsCount; i++){
                            showProduct(allPro[i].name , allPro[i].amount , allPro[i].price);
                        } 
                    } else {
                        string commands[2];
                        istringstream stream;
                        stream.str(command);
                        stream >> commands[0] >> commands[1];
                        // ----------------------- show -----------------------------------
                        if (commands[0] == "show"){
                            bool isFound = false;
                            for(int i = 0; i < productsCount && !isFound; i++){
                                if(allPro[i].name == commands[1]){
                                    showProduct(allPro[i].name , allPro[i].amount , allPro[i].price);
                                    isFound = true;
                                }
                            }
                            if(!isFound){
                                cout << "Invalid product !!!\n";
                            }
                        } 
                        // ----------------------- buy -----------------------------------
                        else if (commands[0] == "buy"){
                            bool isFound = false;
                            for(int i = 0; i < productsCount && !isFound; i++){
                                if(allPro[i].name == commands[1]){
                                    if (allPro[i].amount > 0 && currentUser.walletAmount >= allPro[i].price){
                                        (allPro[i].amount)--;
                                        cout << "You bought one " << allPro[i].name << '\n';
                                        if (allPro[i].amount == 0){
                                            Product* temp = new Product[currentArrayLen];
                                            for(int i = 0 , currentIndex = 0; i < productsCount;i++){
                                                if(allPro[i].name != commands[1]){
                                                    temp[currentIndex++] = allPro[i];
                                                }
                                            }
                                            productsCount--;
                                            delete[] allPro;
                                            allPro = temp;
                                        }
                                    }
                                    else if (currentUser.walletAmount >= allPro[i].price){
                                        cout << "Your balance is not enogh to buy" << allPro[i].name << " !!\n";
                                    }
                                    isFound = true;
                                }
                            }
                            if(!isFound){
                                cout << "Invalid product !!!\n";
                            }
                        }
                        else if(commands[0] == "help"){
                            if(commands[1] == "show"){
                                cout << "show            shows all products\n";
                                cout << "show [product]  shows product information\n";
                            } 
                            else if (commands[1] == "balance"){
                                cout << "balance    shows your wallet amount!!\n";
                            } 
                            else if (commands[1] == "buy"){
                                cout << "buy [product]     buy one of the products\n";
                            }
                            else {
                                cout << "Invalid command for help\n";
                            }
                        }
                        else {
                            cout << "Invalie command\n";
                        }
                    }
                    getCommand(prompt , command);
                }
                quit();
                return 0;
            }
        } else {
            quit();
            return 0;
        }
    } else if (deleteSpace(command) == "q"){
        quit();
        return 0;
    }
    return 0;
}
