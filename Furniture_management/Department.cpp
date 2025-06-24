#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Product.h"
#include "Department.h"
using namespace std;

Department::Department(string name) {
	Product* pHead = nullptr;
	Product* pTail = nullptr;
	Product* pTraverse = nullptr;
	noOfProduct = 0;
}

//for testing, this function will receive product's info from Main.cpp
//after complete all core functions, then only get user input
void Department::addItem(Product* newProduct) {
	if (!pHead) {
		pHead = newProduct;
	}
	else {
		Product* temp = pHead;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newProduct;
	}
	noOfProduct++;
	cout << "Product added successfully.\n";
}


void Department::displayItem() {
	pTraverse = pHead;
	if (!pTraverse) {
		cout << "No products in this department.\n";
		return;
	}

	cout << left << setw(15) << "Product ID"
		<< setw(20) << "Name"
		<< setw(15) << "Colour"
		<< setw(10) << "Price"
		<< setw(10) << "Stock" << endl;
	cout << string(70, '-') << endl;

	while (pTraverse != nullptr) {
		cout << left << setw(15) << pTraverse->PID
			<< setw(20) << pTraverse->productName
			<< setw(15) << pTraverse->colour
			<< "RM" << setw(8) << fixed << setprecision(2) << pTraverse->price
			<< setw(10) << pTraverse->stock << endl;
		pTraverse = pTraverse->next;
	}
}

//Use insertion sort technique to sort the product by Price.
void Department::sortItemByPrice(bool ascending) {
	if (pHead == nullptr || pHead->next == nullptr)
	{
		return;
	}
	Product* sorted = nullptr;
		Product* current = pHead;

		while (current != nullptr)
		{
			Product* next = current->next;
			Product** ptr = &sorted;
			while (*ptr != nullptr) {
				bool comparison = ascending ?
					((*ptr)->price < current->price) :  // Ascending
					((*ptr)->price > current->price);   // Descending

				if (comparison) {
					ptr = &((*ptr)->next);
				}
				else {
					break;
				}
			}

			// Insert current node
			current->next = *ptr;
			*ptr = current;

			current = next;  // Move to next node
		}

	// Update head and tail pointers
	pHead = sorted;
	pTail = pHead;
	while (pTail != nullptr && pTail->next != nullptr) {
		pTail = pTail->next;
	}
}

//Use Binary Search technique to search by Product ID.
Product* Department::binarySearchByPID(const string& targetPID) {
	vector<Product*> productList = toVector();	//Since we use linked list, we need to change the data format to vector to do the binary search.

	// Sort vector by PID first
	sort(productList.begin(), productList.end(), [](Product* a, Product* b) {
		return a->PID < b->PID;
		});

	// Run binary search
	int left = 0;
	int right = productList.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (productList[mid]->PID == targetPID)
			return productList[mid];
		else if (productList[mid]->PID < targetPID)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return nullptr; //If the target not found it will return.
}

//Use Sentinel Search technique to search by Product ID.
Product* Department::sentinelSearchByPID(const string& targetPID) {
	if (!pHead) return nullptr;

	// Create sentinel node with target PID
	Product* sentinel = new Product(targetPID, "", "", 0.0, 0);

	// Go to the end of the list
	Product* temp = pHead;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	// Attach sentinel at the end temporarily
	temp->next = sentinel;

	// Search for the target PID
	Product* current = pHead;
	while (current->PID != targetPID) {
		current = current->next;
	}

	// Remove sentinel
	temp->next = nullptr;
	delete sentinel;

	// If sentinel was reached, item not found
	if (current == sentinel) return nullptr;

	return current;
}

//Use Sentinel Search technique to search by Product name
bool Department::searchItemByName(string keyword) {
	if (!pHead) return false;

	// Create sentinel
	Product* sentinel = new Product(keyword, keyword, "", 0.0, 0);
	Product* temp = pHead;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = sentinel;

	// Search
	Product* current = pHead;
	bool found = false;
	while (true) {
		if (current->PID == keyword || current->productName == keyword) {
			if (current == sentinel) break;
			cout << "\nFound Product:\n";
			cout << "ID: " << current->PID << "\nName: " << current->productName
				<< "\nColour: " << current->colour << "\nPrice: RM" << current->price
				<< "\nStock: " << current->stock << "\n";
			found = true;
			return found;
		}
		current = current->next;
	}

	// Remove sentinel
	temp->next = nullptr;
	delete sentinel;

	if (!found) {
		cout << "No matching product found.\n";
	}
}

vector<Product*> Department::toVector() {
	vector<Product*> list;
	Product* current = pHead;
	while (current != nullptr) {
		list.push_back(current);
		current = current->next;
	}
	return list;
}

void Department::editStock(string targetPID) { //This Function is use to edit the product stock number.

	Product* current = binarySearchByPID(targetPID);

		//If the product ID is not found, it will show this message.
		if (current == nullptr) {
			cout << "Product with ID " << targetPID << " not found.\n";
			return;
		}

		cout << "Current stock for Product ID " << targetPID << ": " << current->stock << endl;

		//Insert new stock quantity.
		int newStock;
		cout << "Enter new stock quantity: ";
		cin >> newStock;

		// To validate the stock is not negative number.
		if (newStock < 0) {
			cout << "Stock cannot be negative. Operation cancelled.\n";
			return;
		}

		current->stock = newStock;
		cout << "Stock updated successfully.\n";
}

//This function can let user to input the target item ID and delete the Item.
void Department::deleteItem(string targetPID) {
	Product* target = sentinelSearchByPID(targetPID);

	if (!target) {
		cout << "Product with ID " << targetPID << " not found.\n";
		return;
	}

	Product* current = pHead;
	Product* previous = nullptr;

	while (current != nullptr && current != target) {
		previous = current;
		current = current->next;
	}

	if (current == nullptr) return; // safety check

	//Update pHead if target is first data.
	if (previous == nullptr) {
		pHead = current->next;
	}
	else {
		previous->next = current->next;
	}
	
	//Update pTail if the target is last data.
	if (pTail == current) {
		pTail = previous;
	}

	delete current;
	noOfProduct--;

	cout << "Product with ID " << targetPID << " deleted successfully.\n";
}

int Department::getNoOfProduct() {
	return noOfProduct;
}

void Department::saveToFile(ofstream& outFile) {
	Product* current = pHead;
	while (current != nullptr) {
		//write into file
		outFile << current->PID << ','
			<< current->productName << ','
			<< current->colour << ','
			<< current->price << ','
			<< current->stock << '\n';
		current = current->next;
	}
}

void Department::loadFromFile(ifstream& inFile) {
	string line;
	Product* last = nullptr;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string pid, name, colour, priceStr, stockStr;

		getline(ss, pid, ',');
		getline(ss, name, ',');
		getline(ss, colour, ',');
		getline(ss, priceStr, ',');
		getline(ss, stockStr, ',');

		float price = stof(priceStr);
		int stock = stoi(stockStr);

		Product* newProd = new Product(pid, name, colour, price, stock);

		if (!pHead) {
			pHead = pTail = newProd;
		}
		else {
			pTail->next = newProd;
			pTail = newProd;
		}
		noOfProduct++;
	}
}
