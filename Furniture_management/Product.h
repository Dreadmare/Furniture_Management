//Product.h by Group BITI-07
//Group memeber: Chee Fang Yee, Soon Boon Ming, Muhd Aiman Hakimi Bin Mohd Hafizi, Wong Man Yee, Lim Jia Hui
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;

//Think this class Product as Node in linked list. By Chee Fang Yee.
class Product {
public:
	string PID;
	string productName;
	string colour;
	float price;
	int stock;

	//each node has info like id, name, colour...
	Product(string id, string productName, string colour, float price, int stock);
	Product* next;
};

#endif
