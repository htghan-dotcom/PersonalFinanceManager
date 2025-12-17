#include <iostream>
#include <string>
#include "Wallet.h"

using namespace std;


int findWalletIndexByID(const Wallet* wallets, int walletCount, const string& id) {
	for (int i = 0; i < walletCount; ++i) {
		if (wallets[i].ID == id) {
			return i;
		}
	}
	return -1;
}


int askAndFindWalletIndexByID(const Wallet* wallets, int walletCount) {
	cout << "\n---TIM VI THEO ID---\n";
	cout << "Vui long nhap ID cua vi can tim: ";
	string id;
	cin >> id;
	cout << endl;
	return findWalletIndexByID(wallets, walletCount, id);
}


void addWallet(Wallet*& wallets, int& walletCount) {
	cout << "\n---THEM VI---\n";
	Wallet newWallet;

	cout << "Vui long nhap thong tin cua vi moi:\n";

	cout << "Nhap ID: ";
	cin >> newWallet.ID;

	cout << "Nhap ten vi: ";
	getline(cin >> std::ws, newWallet.name);

	cout << "Nhap so du cua vi: ";
	cin >> newWallet.balance;


	if (findWalletIndexByID(wallets, walletCount, newWallet.ID) != -1) {
		cout << "LOI: ID da ton tai. Khong them.\n";
		return;
	}


	Wallet* newArr = new Wallet[walletCount + 1];


	for (int i = 0; i < walletCount; ++i) {
		newArr[i] = wallets[i];
	}

	newArr[walletCount] = newWallet;

	delete[] wallets;
	wallets = newArr;
	++walletCount;

	cout << "Da cap nhat xong vi!\n";
}


void editWallet(Wallet* wallets, int walletCount) {
	cout << "\n---CHINH SUA VI---\n";
	cout << "Vui long nhap ID vi can sua thong tin: ";
	string idToEdit;
	cin >> idToEdit;

	int index = findWalletIndexByID(wallets, walletCount, idToEdit);
	if (index == -1) {
		cout << "Khong tim thay thong tin vi can chinh sua!\n";
		return;
	}

	cout << "Vui long nhap thong tin can sua (ID/name/balance): ";
	string field;
	cin >> field;

	if (field == "ID") {
		cout << "Vui long nhap ID moi: ";
		string newID;
		cin >> newID;

		if (findWalletIndexByID(wallets, walletCount, newID) != -1) {
			cout << "LOI: ID moi da ton tai. Khong cap nhat.\n";
			return;
		}
		wallets[index].ID = newID;
	}
	else if (field == "name") {
		cout << "Vui long nhap ten vi moi: ";
		getline(cin, wallets[index].name);
	}
	else if (field == "balance") {
		cout << "Vui long nhap lai so du: ";
		double newBalance;
		cin >> newBalance;
		wallets[index].balance = newBalance;
	}
	else {
		cout << "Truong khong hop le! Chi ho tro: ID / name / balance\n";
		return;
	}

	cout << "\n---DA CAP NHAT THANH CONG!---\n";
}


void deleteWallet(Wallet*& wallets, int& walletCount) {
	cout << "\n---XOA VI---\n";
	cout << "Vui long nhap ID vi can xoa: ";
	string idToDelete;
	cin >> idToDelete;

	int index = findWalletIndexByID(wallets, walletCount, idToDelete);
	if (index == -1) {
		cout << "Khong tim thay vi de xoa!\n";
		return;
	}

	if (walletCount - 1 == 0) {
		delete[] wallets;
		wallets = nullptr;
		walletCount = 0;
		cout << "Da xoa Vi ID[" << idToDelete << "] thanh cong.\n";
		return;
	}

	Wallet* newArr = new Wallet[walletCount - 1];

	for (int i = 0, j = 0; i < walletCount; ++i) {
		if (i == index) continue;
		newArr[j++] = wallets[i];
	}

	delete[] wallets;
	wallets = newArr;
	--walletCount;

	cout << "Da xoa Vi ID[" << idToDelete << "] thanh cong.\n";
}

void updateWalletBalance(Wallet* wallets, int walletCount, string walletID, double amount) {
	int index = findWalletIndexByID(wallets, walletCount, walletID);

	if (index != -1) {
		wallets[index].balance += amount;
		cout << "Da cap nhat so du cho Vi ID[" << walletID << "]. So du moi: " << wallets[index].balance << "\n";
	}
	else {
		cout << " LOI CAP NHAT: Khong tim thay Vi ID " << walletID << ".\n";
	}
}