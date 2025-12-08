#include <iostream>
#include <string>
#include "Income.h"

using namespace std;

int findIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount, string id) {
	int index = -1;
	for (int i = 0; i < IncomeCount; i++) {
		if (sources[i].ID == id) {
			return i;
		}
	}
	return -1;
}
int askAndFindIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount) {
	cout << "\n---TIM NGUON THU THEO ID---\n";
	cout << "Vui long nhap ID cua nguon thu can tim: ";
	string id;
	cin >> id;
	cout << endl;
	return findIncomeSourceIndexByID(sources, IncomeCount, id);
}
void addIncomeSource(IncomeSource*& sources, int& IncomeCount) {
	cout << "\n---THEM NGUON THU---\n";
	IncomeSource newSource;
	cout << "Vui long nhap thong tin nguon thu moi:\n";

	cout << "Nhap ID: ";
	cin >> newSource.ID;

	cout << "Nhap ten vi: ";
	getline(cin, newSource.name);

	if (findIncomeSourceIndexByID(sources, IncomeCount, newSource.ID) != -1) {
		cout << "LOI: ID da ton tai. Khong them.\n";
		return;
	}


	IncomeSource* newArr = new IncomeSource[IncomeCount + 1];


	for (int i = 0; i < IncomeCount; ++i) {
		newArr[i] = sources[i];
	}

	newArr[IncomeCount] = newSource;

	delete[] sources;
	sources = newArr;
	++IncomeCount;

	cout << "Da cap nhat xong vi!\n";
}


void editIncomeSource(IncomeSource* sources, int count) {
	cout << "\n---CHINH SUA NGUON THU---\n";
	string ID;
	cout << "Nhap ID cua nguon thu can thay doi: ";
	cin >> ID;
	int index = -1;
	index = findIncomeSourceIndexByID(sources, count, ID);
	if (index == -1) {
		cout << "Khong the tim thay vi de chinh sua.\n";
		return;
	}
	string field;
	cout << "Vui long nhap thong tin can chinh sua cua nguon thu: ";
	cin >> field;
	if (field == "ID") {
		cout << "Vui long nhap ID moi: ";
		string newID;
		cin >> newID;

		if (findIncomeSourceIndexByID(sources, count, newID) != -1) {
			cout << "LOI: ID moi da ton tai. Khong cap nhat.\n";
			return;
		}
		sources[index].ID = newID;
	}
	else if (field == "name") {
		cout << "Vui long nhap ten vi moi: ";
		getline(cin, sources[index].name);
	}
	else {
		cout << "Truong hop khong hop le. \n";
		return;
	}
	cout << "\n---DA CAP NHAT THANH CONG---\n";
}
void deleteIncomeSource(IncomeSource*& sources, int& count) {
	cout << "\n---XOA NGUON THU---\n";
	string IDToDelete;
	cout << "Nhap ID cua nguon thu can xoa: ";
	cin >> IDToDelete;
	cout << endl;

	int index = -1;
	index = findIncomeSourceIndexByID(sources, count, IDToDelete);
	if (index != -1) {
		cout << "Khong tim thay nguon thu de xoa.\n";
		return;
	}
	if (count == 1) {
		delete sources;
		sources = nullptr;
		count = 0;
		cout << "Da xoa vi ID( " << IDToDelete << ") " << "thanh cong.\n";
		return;
	}
	IncomeSource* newArr = new IncomeSource[count - 1];

	for (int i = 0, j = 0; i < count; ++i) {
		if (i == index) continue;
		newArr[j++] = sources[i];
	}

	delete[] sources;
	sources = newArr;
	--count;

	cout << "Da xoa Vi ID[" << IDToDelete << "] thanh cong.\n";
}


void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount) {

}
void printIncomeTransaction(IncomeTransaction t);
void filterIncomeByDateRange(Date from, Date to);
void filterIncomeByWallet(int walletID, Date from, Date to);