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

void Department::sortItem() {

}

void Department::searchPriceAsc() {

}

void Department::editStock() {

}

void Department::deleteItem() {

}

int Department::getNoOfProduct() {
	return noOfProduct;
}

