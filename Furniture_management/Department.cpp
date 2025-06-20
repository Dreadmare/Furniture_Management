#include <iostream>
#include <string>
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
}

//
void Department::displayItem() {
	pTraverse = pHead;
	while (pTraverse != 0) {
		cout << "Product ID: " << pTraverse->PID << endl;
		cout << "Product name: " << pTraverse->productName << endl;
		cout << "Product colour: " << pTraverse->colour << endl;
		cout << "Product price: RM" << pTraverse->price << endl;
		cout << "Available stock: " << pTraverse->stock << "\n\n";

		pTraverse = pTraverse->next;
	}
}

void Department::sortItem(bool ascending) {
	if (pHead == nullptr || pHead->next == nullptr
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
            } else {
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
		}

}

void Department::searchPriceAsc() {
	if (!pHead) {
		cout << "No products to display.\n";
        return;
	}
	
	
}

void Department::editStock(string targetPID) { //This Function is use to edit the product stock number.

		Product* current = pHead;
		while (current != nullptr && current->PID != targetPID) {
			current = current->next;
		}

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
	Product* current = pHead;
	Product* previous = nullptr;

	while (current != nullptr && current->PID != targetPID) {
		previous = current;
		current = current->next;
	}

	if (current == nullptr) {
		cout << "Product with ID " << targetPID << " not found.\n";
		return;
	}

	// Update pHead if the target is at pHead.
	if (previous == nullptr) {
		pHead = current->next;
	}
	else {
		previous->next = current->next;
	}

	//Update pTail if last item was deleted.
	if (current->next == nullptr && pTail == current) {
		pTail = previous;
	}

	delete current;
	noOfProduct--;

	cout << "Product with ID " << targetPID << " deleted successfully.\n";
}

int Department::getNoOfProduct() {
	return noOfProduct;
}

