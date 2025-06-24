#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
#include "Product.h"
#include <vector>
#include <algorithm>
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
	void sortItemByPrice(bool ascending = true);
	bool searchItemByName(string);
	void editStock(Product* TargetID);
	void deleteItem(Product* TargetID);
	vector<Product*> toVector();
	Product* binarySearchByPID(const string& targetPID);
	Product* sentinelSearchByPID(const string& targetPID);
	int getNoOfProduct();

	//file operation
	void saveToFile(ofstream& outFile);
	void loadFromFile(ifstream& inFile);
};

#endif
