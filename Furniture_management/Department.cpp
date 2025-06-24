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

//Sorting price in asc order from lowest to highest price
void Department::searchPriceAsc() {
	if (!pHead) {
        cout << "No products available.\n";
        return;
    }
    
    // Create temporary array for sorting
    int n = noOfProduct;
    Product** arr = new Product*[n];
    
    // Copy products to array
    Product* current = pHead;
    for (int i = 0; i < n; i++) {
        arr[i] = current;
        current = current->next;
    }

    // Insertion sort (ascending order)
    for (int i = 1; i < n; i++) {
        Product* key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j]->price > key->price) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    // Display sorted products
    for (int i = 0; i < n; i++) {
        cout << "Product ID: " << arr[i]->PID << endl;
        cout << "Product name: " << arr[i]->productName << endl;
        cout << "Product colour: " << arr[i]->colour << endl;
        cout << "Product price: RM" << arr[i]->price << endl;
        cout << "Available stock: " << arr[i]->stock << "\n\n";
    }

    delete[] arr;
}

void Department::editStock() {

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

