#include <iostream>
#include <string>
#include "Wallet.h"

using namespace std;

int findWalletIndexByID(Wallet* wallets, int walletCount, string id) {
	cout << "\n---TIM VI THEO ID---\n";
	for (int i = 0; i < walletCount; i++) {
		if (wallets[i].ID == id) {
			return i;
		}
	}
	return -1;
}
void addWallet(Wallet* wallets, int walletCount, Wallet NewWallet) {
	cout << "\n---THEM VI---\n";
	Wallet* temp = (Wallet*)realloc(wallets, (walletCount + 1) * sizeof(Wallet));
	cout << "Vui long nhap thong tin cua vi moi:" << endl;
	cout << "Nhap ID: ";
	cin >> NewWallet.ID;
	cout << endl;
	cout << "Nhap ten vi: ";
	cin >> NewWallet.ID;
	cout << endl;
	cout << "Nhap so du cua vi: ";
	cin >> NewWallet.balance;
	cout << "Da cap nhat xong vi!";
}
void editWallet(Wallet* wallets, int walletCount) {
	cout << "\n---CHINH SUA VI---\n";
	string edit;
	string IDToDelete;
	cout << "Vui long nhap vi can sua thong tin: ";
	cin >> IDToDelete;
	int index = -1;
    index = findWalletIndexByID(wallets, walletCount, IDToDelete);
	if (index != -1) {
		cout << "Vui long nhap thong tin can sua: ";
		cin >> edit;
		if (edit == "ID") {
			cout << "Vui long nhap thong tin ID can sua: ";
			string ID;
			cin >> ID;
			wallets[index].ID = ID;
		}
		if (edit == "name") {
			cout << "Vui long nhap thong tin ten vi can sua: ";
			string name;
			cin >> name;
			wallets[index].name = name;
		}
		if (edit == "balance") {
			cout << "Vui long nhap lai so du: ";
			double balance;
			cin >> balance;
			wallets[index].balance = balance;
		}
		cout << "\n---DA CAP NHAT THANH CONG!---\n";
	}
	else {
		cout << "Khong tim thay thong tin vi can chinh sua!\n";
	}
}
void deleteWallet(Wallet* wallets, int walletCount) {
	cout << "\n---XOA VI---\n";
	string IDToDelete;
	int index = -1;
	if (index != -1) {
		for (int i = index; i < walletCount - 1; ++i) {
			wallets[i] = wallets[i + 1];
		}
		walletCount--;
		wallets = (Wallet*)realloc(wallets, walletCount * sizeof(Wallet));
		cout << " Da xoa Vi ID[" << IDToDelete << "] thanh cong.\n";
	}
	else {
		cout << "Khong tim thay vi de xoa!";
		
	}
}
void updateWalletBalance(Wallet* wallets, int walletCount, int walletID, double amount) {
	int index = findWalletIndexByID(wallets, walletCount, walletID);

	if (index != -1) {
		wallets[index].balance += amount;
	}
	else {
		cout << " LOI CAP NHAT: Khong tim thay Vi ID " << walletID << ".\n";
	}
}