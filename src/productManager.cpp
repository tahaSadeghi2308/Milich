#include "../include/productManager.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Product* getAllProducts(string fileAddress ,int& currentProductsCount , int& arraySize){
    int initial_count = 15;
    // make sure u delete this 
    Product* products = new Product[initial_count];

    ifstream file;
    file.open(fileAddress);
    if (file.is_open()){

        int count = 0;
        while (!file.eof()){

            if (count == initial_count){
                initial_count *= 2;
                Product* temp = new Product[initial_count];  
                // copy
                for(int i {0}; i < initial_count / 2; i++){
                    temp[i] = products[i];
                }
                delete[] products;
                products = temp;
            }

            Product temp;
            string line;
            getline(file , line);
            if (line != ""){
                stringstream currentLine;
                currentLine.str(line);
                string amount , price;
                currentLine >> temp.name;
                currentLine >> amount;
                currentLine >> price;

                temp.amount = stoi(amount);
                temp.price = stoi(price);

                products[count++] = temp;
            }
        }
        currentProductsCount = count;
        arraySize = initial_count;
        file.close();
    }
    return products;
}

void showProduct(string name , int amount , int price){
    cout << setw(12) << name << setw(12) << amount << setw(12) << price << '\n';
}

bool productExist(Product* allPro , int productCount , string productName){
    for(int i = 0;i < productCount; i++){
        if(allPro[i].name == productName){
            return true;
        }
    }
    return false;
}
