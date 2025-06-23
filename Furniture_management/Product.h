#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;

//Think this class Product as Node in linked list.
class Product {
public:
	string PID;
	string productName;
	string colour;
	float price;
	int stock;

	//each node has info like id, name, colour...
	Product(string id, string productName, string colour, double price, int stock);
	Product* next;
};

#endif
