//InventorySystem.h by Group BITI-07
//Group memeber: Chee Fang Yee, Soon Boon Ming, Muhd Aiman Hakimi Bin Mohd Hafizi, Wong Man Yee, Lim Jia Hui
#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H
#include <iostream>
#include <fstream>
#include <string>
#include "Department.h"
using namespace std;

enum DeptType {
	BEDROOM, LIVING_ROOM, KITCHEN, BATHROOM, OTHERS, //default bedroom=0, living room=1...
	DEPT_COUNT //end with counting number of types in total = 5
};

const string deptName[] = { "Bedroom", "Living room", "Kitchen", "Bathroom", "Others" };

class InventorySystem {
public:
	Department* dept[5];

	InventorySystem(); //constructor
	~InventorySystem(); //destructor
	void menu(); //Menu interface by Wong Man Yee
	bool isPIDUniqueAcrossDepartments(const string& PID); //Check PID is unique by Wong Man Yee

	//file operation
	void saveAllDepartments(); //save all data to file by Lim Jia Hui
	void loadAllDepartments(); //Load data from file by Lim Jia Hui
};

#endif
