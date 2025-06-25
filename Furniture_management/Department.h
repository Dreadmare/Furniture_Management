//Department.h by Group BITI-07
//Group memeber: Chee Fang Yee, Soon Boon Ming, Muhd Aiman Hakimi Bin Mohd Hafizi, Wong Man Yee, Lim Jia Hui
#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
#include "Product.h"
#include <vector>
#include <algorithm>
using namespace std;

//This class is like the linked list of products 
//for a certain department, such as list of products in Bedroom department. By Chee Fang Yee
class Department {
private:
	string departmentName;
	Product* pHead;
	Product* pTail;
	Product* pTraverse;
	int noOfProduct;

public:
	Department(string name);
	void addItem(Product* newProduct); //By Chee Fang Yee
	void displayItem(); //By Chee Fang Yee
	void sortItemByPrice(bool ascending = true); //By Muhd Aiman Hakimi
	void searchItemByName(string); //By Soon Boon Ming
	void editStock(Product* TargetID); //By Lim Jia Hui
	void deleteItem(Product* TargetID); //By Lim Jia Hui
	vector<Product*> toVector(); //By Soon Boon Ming
	Product* binarySearchByPID(const string& targetPID); //By Soon Boon Ming
	Product* sentinelSearchByPID(const string& targetPID); //By Soon Boon Ming
	int getNoOfProduct(); //By Chee Fang Yee

	//file operation
	void saveToFile(ofstream& outFile); //By Lim Jia Hui
	void loadFromFile(ifstream& inFile); //By Lim Jia Hui
};

#endif
