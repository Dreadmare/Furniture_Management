#include <iostream>
#include <string>
#include "InventorySystem.h"
using namespace std;

int main() {
	InventorySystem system;
	//initialize product info for testing stage
	Product* p1 = new Product("P456", "chair", "black", 199.99, 10);
	Product* p2 = new Product("P4199", "bed", "white", 1.33, 90);

	system.dept[BEDROOM]->addItem(p1);
	system.dept[BEDROOM]->addItem(p2);

	system.dept[BEDROOM]->displayItem();

	return 0;
}