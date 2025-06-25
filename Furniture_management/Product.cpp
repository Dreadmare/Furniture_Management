//Product.cpp by Group BITI-07
//Group memeber: Chee Fang Yee, Soon Boon Ming, Muhd Aiman Hakimi Bin Mohd Hafizi, Wong Man Yee, Lim Jia Hui
#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

//Once class product been called, class Product will 
//receive argument which is the info needed. By Chee Fang Yee.
Product::Product(string PID, string productName, string colour, float price, int stock) {
	this->PID = PID; 
	this->productName = productName;
	this->colour = colour;
	this->price = price; 
	this->stock = stock;
	//initialize pointer = NULL
	Product* next = nullptr;
}
