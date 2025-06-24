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
    loadAllDepartments(); //load form file on startup
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
    string input;
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
        getline(cin, input); // read as string first

        // validate if input is number
        if (input.empty() || input.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }
        choice = stoi(input); // convert to int
        if (choice < 1 || choice > 7) {
            cin.clear();
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

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
            cin.ignore();
            deptChoice --;
            if (deptChoice < 0 || deptChoice >= DEPT_COUNT) {
                cout << "Invalid department selection.\n";
                break;
            }
            string id, name, colour;
            float price;
            int stock;
            cout << "Enter Product ID: ";
            cin >> id;
            if (!isPIDUniqueAcrossDepartments(id)) { //Check the input PID already exists or not.
                cout << "Product ID " << id << " already exists.\n";
                break;
            }
            cout << "Enter Product Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Colour: ";
            getline(cin, colour);
            // Validate price input
            while (true) {
                cout << "Enter Price: ";
                cin >> price;
                if (cin.fail() || price < 0) {
                    cout << "Invalid price. Please enter a valid positive number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    break;
                }

            }

            // Validate stock input
            while (true) {
                cout << "Enter Stock: ";
                cin >> stock;
                if (cin.fail() || stock < 0) {
                    cout << "Invalid stock. Please enter a valid non-negative number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    break;
                }
            }
            dept[deptChoice]->addItem(new Product(id, name, colour, price, stock));
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            string keyword;
            cin.ignore(); // to clear newline left in input buffer
            cout << "Enter Product ID or Name to search: ";
            getline(cin, keyword);

            bool found = false;
            for (int i = 0; i < DEPT_COUNT; i++) {
                Product* byID = dept[i]->sentinelSearchByPID(keyword);
                if (byID) {
                    cout << "\nFound in " << deptName[i] << " Department:\n";
                    cout << "Product ID: " << byID->PID << "\nName: " << byID->productName
                        << "\nColour: " << byID->colour << "\nPrice: RM" << byID->price
                        << "\nStock: " << byID->stock << endl;
                    found = true;
                    break; // stop after first found match (or remove to find duplicates)
                }
            }

            // If not found by ID, try by Name
            if (!found) {
                for (int i = 0; i < DEPT_COUNT; i++) {
                    bool nameFound = dept[i]->searchItemByName(keyword);
                    if (nameFound) found = true;
                }
            }

            if (!found) {
                cout << "Product with ID or Name '" << keyword << "' not found in any department.\n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        case 5: {
            string id;
            cout << "Enter Product ID to edit stock: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < DEPT_COUNT; i++) {
                Product* result = dept[i]->binarySearchByPID(id);
                if (result) {
                    dept[i]->editStock(result);
                    found = true;
                    break; // stop checking other departments
                }
            }

            if (!found) {
                cout << "Product with ID " << id << " not found in any department.\n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        case 6: {
            string id;
            cout << "Enter Product ID to delete: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < DEPT_COUNT; i++) {
                Product* result = dept[i]->sentinelSearchByPID(id);
                if (result) {
                    dept[i]->deleteItem(result);
                    found = true;
                    break; // stop checking other departments
                }
            }
            if (!found) { //If not found then output this message.
                cout << "Product with ID " << id << " not found in any department.\n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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