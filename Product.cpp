#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

//once class product been called, class Product will 
//receive argument which is the info needed.
Product::Product(string PID, string productNname, string colour, float price, int stock) {
	this->PID = PID; 
	this->productName = productName;
	this->colour = colour;
	this->price = price; 
	this->stock = stock;
	//initialize pointer = NULL
	Product* next = nullptr;
}

