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

bool InventorySystem::isPIDUniqueAcrossDepartments(const string& PID) {
    for (int i = 0; i < DEPT_COUNT; ++i) {
        if (dept[i]->sentinelSearchByPID(PID) != nullptr)
            return false;
    }
    return true;
}

void InventorySystem::menu() {
    int choice;
    bool running = true;

    while (running) {
        cout << "\n********************************************************\n";
        cout << "\tWELCOME TO FURNITURE INVENTORY MANAGEMENT\n";
        cout << "********************************************************\n";
        cout << "1. Display Product\n";
        cout << "2. Add Product\n";
        cout << "3. Sort Product by Price\n";
        cout << "4. Search Product by PID Or Name\n";
        cout << "5. Edit Product Stock\n";
        cout << "6. Delete Product\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            for (int i = 0; i < DEPT_COUNT; i++) {
                cout << "\n--- " << deptName[i] << " Department ---\n";
                dept[i]->displayItem();
            }
            break;
        }
        case 2: {
            int deptChoice;
            cout << "\nSelect Department:\n";
            for (int i = 0; i < DEPT_COUNT; ++i)
                cout << i+1 << ". " << deptName[i] << endl;
            cin >> deptChoice;
            deptChoice -= 1;
            if (deptChoice < 0 || deptChoice >= DEPT_COUNT) {
                cout << "Invalid department selection.\n";
                break;
            }
            string id, name, colour;
            float price;
            int stock;
            cout << "Enter Product ID: ";
            cin >> id;
            if (!isPIDUniqueAcrossDepartments(id)) {
                cout << "Product ID " << id << " already exists.\n";
                break;
            }
            cout << "Enter Product Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Colour: ";
            getline(cin, colour);
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Stock: ";
            cin >> stock;
            dept[deptChoice]->addItem(new Product(id, name, colour, price, stock));
            break;
        }
        case 3: {
            for (int i = 0; i < DEPT_COUNT; i++) {
                dept[i]->sortItemByPrice(true);
            }
            cout << "Products sorted by price in ascending order.\n";
            break;
        }
        case 4: {
            string targetID;
            cout << "Enter Product ID or Name to search: ";
            cin >> targetID;
            for (int i = 0; i < DEPT_COUNT; i++) {
                dept[i]->searchItemName(targetID);
            }
        }
        case 5: {
            string id;
            cout << "Enter Product ID to edit stock: ";
            cin >> id;
            for (int i = 0; i < DEPT_COUNT; i++) {
                dept[i]->editStock(id);
            }
            break;
        }
        case 6: {
            string id;
            cout << "Enter Product ID to delete: ";
            cin >> id;
            for (int i = 0; i < DEPT_COUNT; i++) {
                dept[i]->deleteItem(id);
            }
            break;
        }
        case 7:
            running = false;
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
