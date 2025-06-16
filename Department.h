#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
#include "Product.h"
using namespace std;

//This class is like the linked list of products 
//for a certain department, such as list of products in Bedroom department
class Department {
private:
	string departmentName;
	Product* pHead;
	Product* pTail;
	Product* pTraverse;
	int noOfProduct;

public:
	Department(string name);
	void addItem(Product* newProduct);
	void displayItem();
	void sortItem(bool ascending = true);
	void searchPriceAsc();
	void editStock();
	void deleteItem();

	int getNoOfProduct();
	Product* binarySearchByPrice(float targetPrice);
	Product* sentinelSearchByPrice(float targetPrice);

};

#endif
