#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Department.h"
#include "InventorySystem.h"
using namespace std;

InventorySystem::InventorySystem() {
	//assign name for department array
	//eg. dept[0] is Bedroom, dept[1] is living room
	for (int i = 0; i < DEPT_COUNT; i++) {
		dept[i] = new Department(deptName[i]);
	}
    loadAllDepartments(); //load form file on startup
}

//deconstructor to avoid memory leaking
InventorySystem::~InventorySystem() {
	for (int i = 0; i < DEPT_COUNT; i++) {
		delete dept[i];
	}
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
                cout << "\n\n";
                cout << setw(24) << right << "*** " << deptName[i] << " DEPARTMENT ***\n";
                cout << string(70, '-') << endl;
                dept[i]->displayItem();
            }
            cout << "\nPress enter to continue...\n\n"; 
            cin.ignore();
            cin.get(); 
            break;
        }
        case 2: {       
            int deptChoice;
            cout << "\nSelect Department:\n";
            for (int i = 0; i < DEPT_COUNT; ++i) {
                cout << "\t";
                cout << i + 1 << ". " << deptName[i] << endl;

            }
            cout << "Enter your department choice: ";
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
                cout << "Product ID " << id << " already exists in another department.\n";
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

            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
            break;
        }
        case 3: {       
            for (int i = 0; i < DEPT_COUNT; i++) 
                dept[i]->sortItemByPrice(true);
            cout << "Successfully sort products by price in ascending order!\n\n";

            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
            break;
        }
        case 4: {
            string targetID;
            cout << "Enter Product ID or Name to search: ";
            cin >> targetID;
            for (int i = 0; i < DEPT_COUNT; i++) {
                cout << "\t" << setw(11) << left << deptName[i] << ": ";
                dept[i]->searchItemName(targetID);
            }
            cout << "\nPress enter to continue...\n";
            cin.ignore();
            cin.get();
            break;
        }
        case 5: {
            string id;
            bool edited = false;

            cout << "Enter Product ID to edit stock: ";
            cin >> id;
            for (int i = 0; i < DEPT_COUNT; i++) {
                Product* found = dept[i]->sentinelSearchByPID(id);
                if (found != nullptr) {
                  dept[i]->editStock(id);
                  edited = true;
                  break; // stop after first delete
                }
            }
            if (!edited) {
                cout << "Product with ID " << id << " not found.\n\n";
            }

            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
            break;
        }
        case 6: {
            string id;
            bool deleted = false;

            cout << "Enter Product ID to delete: ";
            cin >> id;
            for (int i = 0; i < DEPT_COUNT; ++i) {
                Product* found = dept[i]->sentinelSearchByPID(id);
                if (found != nullptr) {
                    dept[i]->deleteItem(id);
                    deleted = true;
                    break; // stop after first delete
                }
            }

            if (!deleted) {
                cout << "Product with ID " << id << " not found.\n\n";
            }

            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
            break;
        }
        case 7:
            saveAllDepartments(); //save all to file before close system
            running = false;
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

bool InventorySystem::isPIDUniqueAcrossDepartments(const string& PID) {
    for (int i = 0; i < DEPT_COUNT; ++i) {
        if (dept[i]->sentinelSearchByPID(PID) != nullptr)
            return false;
    }
    return true;
}

void InventorySystem::saveAllDepartments() {
    for (int i = 0; i < DEPT_COUNT; i++) {
        string filename = deptName[i] + ".txt";
        ofstream outFile(filename); //open a file to write
        if (outFile.is_open()) {
            dept[i]->saveToFile(outFile);
            outFile.close();
        }
        else {
            cout << "Failed to save to file: " << filename << endl;
        }
    }
}

void InventorySystem::loadAllDepartments() {
    for (int i = 0; i < DEPT_COUNT; ++i) {
        string filename = deptName[i] + ".txt";
        ifstream inFile(filename);
        if (inFile.is_open()) {
            dept[i]->loadFromFile(inFile);
            inFile.close();
        }
        else {
            // File might not exist yet, ignore it
            continue;
        }
    }
}