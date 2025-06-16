#include <iostream>
#include <fstream>
#include <string>
#include "Department.h"
#include "InventorySystem.h"
using namespace std;

InventorySystem::InventorySystem() {
	//assign name for department array
	//eg. dept[0] is Bedroom, dept[1] is living room
	for (int i = 0; i < DEPT_COUNT; i++) {
		dept[i] = new Department(deptName[i]);
	}
}

//deconstructor to avoid memory leaking
InventorySystem::~InventorySystem() {
	for (int i = 0; i < DEPT_COUNT; i++) {
		delete dept[i];
	}
}

void InventorySystem::menu() {

}
