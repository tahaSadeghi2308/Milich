#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <string>
using namespace std;

// variables
const int PRODUCTS_INITIAL_COUNT = 15;

// structures
struct Product {
    string name;
    int amount , price;
};

// functions
Product* getAllProducts(string , int& );

#endif