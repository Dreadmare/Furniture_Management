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

const string deptName[] = { "BEDROOM", "LIVING ROOM", "KITCHEN", "BATHROOM", "OTHERS" };

class InventorySystem {
public:
	Department* dept[5];


	InventorySystem();
	~InventorySystem();
	void menu();
	bool isPIDUniqueAcrossDepartments(const string& PID);

	//file operation
	void saveAllDepartments();
	void loadAllDepartments();
};

#endif
