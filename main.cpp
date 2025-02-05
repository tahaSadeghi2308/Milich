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
                    updateUsersInfo("../txt_files/users.txt" , users);
                    delete[] users;
                    users = nullptr;
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
            string command;
            getCommand(prompt ,command);
            
            if (currentUser.isAdmin){
                // this is for save and undo
                Product deletedProduct;
                // for admin users
                while(deleteSpace(command) != "q"){
                    clearScreen();
                    string commands[3];
                    istringstream stream;
                    stream.str(command);
                    stream >> commands[0] >> commands[1] >> commands[2];

                    if(commands[0] == "add"){
                        if(commands[1] != "" && commands[2] != ""){
                            if(isNumber(commands[2]) && !isNumber(commands[1])){
                                if(!productExist(allPro , productsCount , commands[1])){
                                    if (productsCount + 1 >= currentArrayLen){
                                        currentArrayLen *= 2;
                                        Product* temp = new Product[currentArrayLen];
                                        for(int i = 0; i < productsCount; i++){
                                            temp[i] = allPro[i];
                                        }
                                        delete[] allPro;
                                        allPro = temp;
                                    } 
                                    Product temp;
                                    temp.name = commands[1];
                                    temp.price = stoi(commands[2]);
                                    temp.amount = 1; // hard coded

                                    allPro[productsCount] = temp;
                                    productsCount++;

                                    cout << "Product added successfully!!\n";
                                }
                                else {
                                    for(int i = 0; i < productsCount; i++){
                                        if (allPro[i].name == commands[1]){
                                            (allPro[i].amount)++;
                                            cout << "One " << commands[1] << " added\n";
                                            break;
                                        }
                                    }
                                }
                            }
                            else {
                                if(!isNumber(commands[2])){
                                    cout << "Price is a number bro not " << commands[2] << '\n';
                                }
                                else {
                                    cout << "You think this is logicall ??\n";
                                }
                            }
                        }
                        else {
                            cout << "Invalid command!!\n";
                            cout << "add [Item] [price]    add a item to our products\n";
                        }
                    }
                    else if (commands[0] == "remove"){
                        if(commands[2] == ""){
                            if (commands[1] != ""){
                                if (productExist(allPro , productsCount , commands[1])){
                                    Product* temp = new Product[currentArrayLen];
                                    for(int i = 0 , currentIndex = 0; i < productsCount; i++){
                                        if(allPro[i].name != commands[1]){
                                            temp[currentIndex++] = allPro[i];
                                        }
                                        else {
                                            deletedProduct = allPro[i];
                                        }
                                    }
                                    productsCount--;
                                    delete[] allPro;
                                    allPro = temp;
                                    cout << commands[1] << " deleted successfully !!\n";
                                }
                                else {
                                    cout << "This product does not exist !!!\n";
                                }
                            }
                            else {
                                cout << "You have to enter an item to remove !!\n";
                            }
                        }
                        else {
                            cout << "Invalid command !!\n";
                        }
                    }
                    else if (commands[0] == "rename"){
                        if(commands[1] != "" && commands[2] != ""){
                            bool isFound = false;
                            for(int i = 0; i < productsCount && !isFound; i++){
                                if(allPro[i].name == commands[1]){
                                    allPro[i].name = commands[2];
                                    isFound = true;
                                    cout << commands[1] << " successfully renamed to " << commands[2] << '\n';
                                }
                            }
                            if (!isFound){
                                cout << commands[1] << " does not exist in our products !!\n";
                            }
                        }
                        else {
                            cout << "Invalid command entered !!\n";
                            cout << "rename [item] [newName]\n";
                        }
                    }
                    else if (commands[0] == "price"){
                        if(commands[1] != "" && commands[2] != ""){
                            if (isNumber(commands[2])){
                                bool isFound = false;
                                for(int i = 0; i < productsCount && !isFound; i++){
                                    if(allPro[i].name == commands[1]){
                                        allPro[i].price = stoi(commands[2]);
                                        isFound = true;
                                        cout << commands[1] << " successfully re-priced to " << commands[2] << '\n';
                                    }
                                }
                                if (!isFound){
                                    cout << commands[1] << " does not exist in our products !!\n";
                                }
                            }
                            else {
                                cout << "New price should be a number !!!\n";
                            }
                        }
                        else {
                            cout << "Invalid command entered !!\n";
                            cout << "price [item] [newPrice]\n";
                        }
                    }
                    else if (commands[0] == "credit"){

                        if(commands[1] != "" && commands[2] != ""){
                            if(isNumber(commands[2])){
                                bool isFound = false;
                                for(int i = 0; i < USERS_COUNT && !isFound; i++){
                                    if(users[i].username == commands[1]){
                                        users[i].walletAmount = stoi(commands[2]);
                                        isFound = true;
                                        cout << "Balance for " << commands[1] << " changed successfully!!\n";
                                    }
                                }
                                if(!isFound){
                                    cout << "This user does not exist !!\n";
                                }
                            }
                            else {
                                cout << "New balance should be a number !!!\n";
                            }
                        }
                        else {
                            cout << "Invalid command entered !!\n";
                            cout << "credit [username] [newBalance]\n";
                        }
                    }
                    else if(commands[0] == "undo"){
                        if(commands[1] == ""){
                            if (deletedProduct.name != ""){
                                allPro[productsCount] = deletedProduct;
                                productsCount++;
                                cout << deletedProduct.name << " is back!!!\n";
                                deletedProduct.name = "";
                            }
                            else {
                                cout << "Nothing to undo !!!\n";
                            }
                        }
                        else {
                            cout << "Invalid command entered !!!\n";
                        }
                    }
                    else {
                        cout << "Invalid Command !!\n";
                    }
                    getCommand(prompt , command);
                }
                quit();
                // ------------------- update files -----------------------------
                updateProductsInfo("../txt_files/products.txt" , allPro , productsCount);
                updateUsersInfo("../txt_files/users.txt" , users);
                releseAllMems(&users , &allPro);
                return 0;
            } else {
                // for normal users
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
                                    cout << setw(12) << "Product Name" << setw(12) << "Amount" << setw(12) << "Price\n";
                                    showProduct(allPro[i].name , allPro[i].amount , allPro[i].price);
                                    isFound = true;
                                }
                            }
                            if(!isFound){
                                cout << "Invalid product to show !!!\n";
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
                                cout << "Invalid product to buy!!!\n";
                            }
                        }
                        else if(commands[0] == "help"){
                            if (commands[1] == ""){
                                cout << "help [command]    shows how does a command works\n";
                            }
                            else if(commands[1] == "show"){
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
                // ------------------- update files -----------------------------
                updateProductsInfo("../txt_files/products.txt" , allPro , productsCount);
                updateUsersInfo("../txt_files/users.txt" , users);
                releseAllMems(&users , &allPro);
                return 0;
            }
        } else {
            quit();
            // ------------------- update files -----------------------------
            updateUsersInfo("../txt_files/users.txt" , users);
            delete[] users;
            users = nullptr;
            return 0;
        }
    } else if (deleteSpace(command) == "q"){
        quit();
        return 0;
    }
    return 0;
}
